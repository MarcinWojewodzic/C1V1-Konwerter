/*
 * SM.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */
#include "SM.h"
#include "bh1750.h"
#include "i2c.h"
#include "main.h"
#include "stdio.h"
#include "supp.h"
#ifndef DEBUG_SWDIO
#include "usart.h"
#endif
#include <Commands.h>
#include <Messages.h>
static void SM_InitializeFunction();
static void SM_RunningFunction();
static void SM_WaitForMeasurmentIsFinished();
static void SM_SleppFunction();
static void SM_ParseUartFunction();
static void SM_DebugFunction();
static void SM_ErrorFunction();
static void SM_ChangeState();
SmTransitionTable_TypeDef TransitionTable[] = { { SM_STATE_INITIALIZE, SM_STATE_RUNNING, SM_EVENT_INITIALIZE_OK },
                                                { SM_STATE_RUNNING, SM_STATE_WAIT_FOR_MEASURMENT_IS_FINISHED, SM_EVENT_START_CONVESION },
                                                { SM_STATE_WAIT_FOR_MEASURMENT_IS_FINISHED, SM_STATE_SLEEP, SM_EVENT_END_RUNNING },
                                                { SM_STATE_SLEEP, SM_STATE_RUNNING, SM_EVENT_END_SLEEP },
                                                { SM_STATE_RUNNING, SM_STATE_PARSE_UART, SM_EVENT_UART },
                                                { SM_STATE_WAIT_FOR_MEASURMENT_IS_FINISHED, SM_STATE_PARSE_UART, SM_EVENT_UART },
                                                { SM_STATE_SLEEP, SM_STATE_PARSE_UART, SM_EVENT_UART },
                                                { SM_STATE_DEBUG, SM_STATE_PARSE_UART, SM_EVENT_UART },
                                                { SM_STATE_PARSE_UART, SM_STATE_RUNNING, SM_EVENT_END_SLEEP } };
SmFunctions_TypeDef Function[]
    = { { SM_InitializeFunction }, { SM_RunningFunction }, { SM_WaitForMeasurmentIsFinished }, { SM_SleppFunction }, { SM_ParseUartFunction },
        { SM_DebugFunction },      { SM_ErrorFunction } };
LsCommands_TypeDef LsCommands[] = { { LS_START_MEASURMENT_COMMAND, sizeof(LS_START_MEASURMENT_COMMAND) - 1 },
                                    { LS_DEBUG_COMMUNICATION_COMMAND, sizeof(LS_DEBUG_COMMUNICATION_COMMAND) - 1 },
                                    { LS_DEBUG_STOP_COMMAND, sizeof(LS_DEBUG_STOP_COMMAND) - 1 } };
Sm_TypeDef SmPtr                = { 0 };
bh1750_t Bh                     = { 0 };
uint8_t SizeUartData            = 0;
uint8_t data[100]               = { 0 };

void SM_MainFunction()
{
   if(HAL_GetTick() - SmPtr.LastTick > 1000)
   {
      SM_ChangeState();
      SmPtr.LastTick = HAL_GetTick();
      if(Function[SmPtr.State].SmFunction != NULL)
      {
         Function[SmPtr.State].SmFunction();
      }
   }
}
static void SM_ChangeState()
{
   for(int i = 0; i < TRANSITION_TABLE_SIZE; i++)
   {
      if(SmPtr.State == TransitionTable[i].Source && SmPtr.NewEvent == TransitionTable[i].Event)
      {
         SmPtr.State = TransitionTable[i].Destination;
      }
   }
   SmPtr.NewEvent = SM_EVENT_NOTHING;
}
static void SM_InitializeFunction()
{
#ifndef DEBUG_SWDIO
   bh1750_Init(&Bh, &hi2c2, 35, One_Time_H_Resolution_Mode);
   SmPtr.DebugFlag = LS_NO_DEBUG;
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   HAL_UARTEx_ReceiveToIdle_DMA(&huart1, data, 100);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)INITIALIZED_COMPLETE, sizeof(INITIALIZED_COMPLETE) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
#endif
   SmPtr.NewEvent = SM_EVENT_INITIALIZE_OK;
}
static void SM_RunningFunction()
{
#ifndef DEBUG_SWDIO
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)STATE_ID_RUNNING, sizeof(STATE_ID_RUNNING) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
#endif
   if(SmPtr.UartFlag == LS_NO_UART_RECIVE)
   {
      SmPtr.NewEvent = SM_EVENT_START_CONVESION;
   }
   else
   {
      SmPtr.NewEvent = SM_EVENT_UART;
   }
}
static void SM_WaitForMeasurmentIsFinished()
{
#ifndef DEBUG_SWDIO
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)STATE_ID_WAIT_FOR_MEASURMENT_IS_FINISHED, sizeof(STATE_ID_WAIT_FOR_MEASURMENT_IS_FINISHED) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
#endif
   if(SmPtr.UartFlag == LS_NO_UART_RECIVE)
   {
      SmPtr.NewEvent = SM_EVENT_END_RUNNING;
   }
   else
   {
      SmPtr.NewEvent = SM_EVENT_UART;
   }
}
static void SM_SleppFunction()
{
#ifndef DEBUG_SWDIO
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)STATE_ID_SLEEP, sizeof(STATE_ID_SLEEP) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   HAL_SuspendTick();
   HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
   HAL_ResumeTick();
#endif
   if(SmPtr.UartFlag == LS_NO_UART_RECIVE)
   {
      SmPtr.NewEvent = SM_EVENT_END_SLEEP;
   }
   else
   {
      SmPtr.NewEvent = SM_EVENT_UART;
   }
}
static void SM_ParseUartFunction()
{
   uint8_t Parse   = 1;
   uint8_t Command = 255;
   for(int i = 0; i < 3; i++)
   {
      Parse = 1;
      for(int j = 0; j < SizeUartData; j++)
      {
         if(data[j] != LsCommands[i].Commands[j])
         {
            Parse = 0;
            break;
         }
      }
      if(Parse == 1)
      {
         Command = i;
         break;
      }
   }
   switch(Command)
   {
      case 0:
      {
         SmPtr.NewEvent = SM_EVENT_END_SLEEP;
         break;
      }
      case 1:
      {
         SmPtr.DebugFlag = LS_DEBUG_COMMUNICATION;
         SmPtr.NewEvent  = SM_EVENT_END_SLEEP;
         break;
      }
      case 2:
      {
         SmPtr.DebugFlag = LS_NO_DEBUG;
         SmPtr.NewEvent  = SM_EVENT_END_SLEEP;
         break;
      }
   }
   if(Command != 255)
   {
#ifndef DEBUG_SWDIO
      HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
      HAL_UART_Transmit(&huart1, (uint8_t *)LsCommands[Command].Commands, LsCommands[Command].SizeCommands, 1000);
      HAL_UART_Transmit(&huart1, (uint8_t *)LS_STATUS_OK, sizeof(LS_STATUS_OK) - 1, 1000);
      HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
#endif
   }
   else if(SmPtr.DebugFlag != LS_DEBUG_COMMUNICATION)
   {
#ifndef DEBUG_SWDIO
      HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
      HAL_UART_Transmit(&huart1, (uint8_t *)LS_STATUS_ERROR, sizeof(LS_STATUS_ERROR) - 1, 1000);
      HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
#endif
   }

   SmPtr.UartFlag = LS_NO_UART_RECIVE;
   SmPtr.NewEvent = SM_EVENT_END_SLEEP;
}
static void SM_DebugFunction()
{
}
static void SM_ErrorFunction()
{
}
#ifndef DEBUG_SWDIO
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
   if(SmPtr.DebugFlag == LS_DEBUG_COMMUNICATION)
   {
      HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
      HAL_UART_Transmit(huart, data, Size, 1000);
      uint8_t d[20];
      uint8_t l = sprintf((char *)d, "%d \n", Size);
      HAL_UART_Transmit(huart, d, l, 1000);
      HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
      HAL_UARTEx_ReceiveToIdle_DMA(huart, data, 1000);
      SizeUartData   = Size;
      SmPtr.UartFlag = LS_UART_RECIVE;
   }
   else
   {
      SizeUartData   = Size;
      SmPtr.UartFlag = LS_UART_RECIVE;
      HAL_UARTEx_ReceiveToIdle_DMA(huart, data, 1000);
   }
}
#endif
