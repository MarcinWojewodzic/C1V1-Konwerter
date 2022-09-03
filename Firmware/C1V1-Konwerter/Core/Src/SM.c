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
#include "usart.h"
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
                                                {} };
SmFunctions_TypeDef Function[]
    = { { SM_InitializeFunction }, { SM_RunningFunction }, { SM_WaitForMeasurmentIsFinished }, { SM_SleppFunction }, { SM_ParseUartFunction },
        { SM_DebugFunction },      { SM_ErrorFunction } };
Sm_TypeDef SmPtr     = { 0 };
bh1750_t Bh          = { 0 };
uint8_t SizeUartData = 0;
uint8_t data[100];

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
   bh1750_Init(&Bh, &hi2c2, 35, One_Time_H_Resolution_Mode);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   HAL_UARTEx_ReceiveToIdle_DMA(&huart1, data, 100);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)INITIALIZED_COMPLETE, sizeof(INITIALIZED_COMPLETE) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   SmPtr.NewEvent = SM_EVENT_INITIALIZE_OK;
}
static void SM_RunningFunction()
{
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)STATE_ID_RUNNING, sizeof(STATE_ID_RUNNING) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   SmPtr.NewEvent = SM_EVENT_START_CONVESION;
}
static void SM_WaitForMeasurmentIsFinished()
{
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)STATE_ID_WAIT_FOR_MEASURMENT_IS_FINISHED, sizeof(STATE_ID_WAIT_FOR_MEASURMENT_IS_FINISHED) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   SmPtr.NewEvent = SM_EVENT_END_RUNNING;
}
static void SM_SleppFunction()
{
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(&huart1, (uint8_t *)STATE_ID_SLEEP, sizeof(STATE_ID_SLEEP) - 1, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   HAL_SuspendTick();
   HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
   HAL_ResumeTick();
   SmPtr.NewEvent = SM_EVENT_END_SLEEP;
}
static void SM_ParseUartFunction()
{
}
static void SM_DebugFunction()
{
}
static void SM_ErrorFunction()
{
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_TRANSMIT);
   HAL_UART_Transmit(huart, data, Size, 1000);
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, LS_LISTENING);
   HAL_UARTEx_ReceiveToIdle_DMA(huart, data, 1000);
}
