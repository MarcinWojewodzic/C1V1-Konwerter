/*
 * SM.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */
#include "SM.h"
#include "MAX485.h"
#include "bh1750.h"
#include "i2c.h"
#include "main.h"
#include "stdio.h"
#include "supp.h"
#include "usart.h"
#include <Messages.h>
static void SM_InitializeFunction();
static void SM_RunningFunction();
static void SM_ChangeState();
SmTransitionTable_TypeDef TransitionTable[] = { { SM_STATE_INITIALIZE, SM_STATE_RUNNING, SM_EVENT_INITIALIZE_OK }, {}, {}, {}, {} };
SmFunctions_TypeDef Function[]              = { { SM_InitializeFunction }, { SM_RunningFunction } };
Sm_TypeDef SmPtr                            = { 0 };
bh1750_t Bh                                 = { 0 };
Max485_Typedef Max                          = { 0 };
uint8_t data[100];

void SM_MainFunction()
{
   if(TIM_GetTick() - SmPtr.LastTick > 10)
   {
      SM_ChangeState();
      SmPtr.LastTick = TIM_GetTick();
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
         SmPtr.State    = TransitionTable[i].Destination;
         SmPtr.NewEvent = SM_EVENT_NOTHING;
         return;
      }
   }
}
static void SM_InitializeFunction()
{
   //   bh1750_Init(&Bh, &hi2c2, 35, One_Time_H_Resolution_Mode);
   Max485_Init(&Max, &huart1, MAX485_Selector_GPIO_Port, MAX485_Selector_Pin);
   Max485_StartListening(&Max, data, 100);
   SmPtr.NewEvent = SM_EVENT_INITIALIZE_OK;
   Max485_SetStateSending(&Max);
   Max485_StartSending(&Max, (uint8_t *)INITIALIZED_COMPLETE, sizeof(INITIALIZED_COMPLETE));
   Max485_SetStateListening(&Max);
}
static void SM_RunningFunction()
{
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
   Max485_ListeningAfterTalk(&Max, data, Size, data, Size);
}
