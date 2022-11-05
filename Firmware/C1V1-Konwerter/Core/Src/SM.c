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
#include "MAXProtocol.h"
#endif
// #define DEBUG_SWDIO
static void SM_ChangeState(void);
static void SM_InitializeFunction(void);
static void SM_RunningFunction(void);
static void SM_WaitForSendFunction(void);
static void SM_SleepFunction(void);
void MAX_CommandTestFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart);
void MAX_CommandStartMeasurmentFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart);
void MAX_CommandGoToDeepSleepFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart);
SmTransitionTable_TypeDef TransitionTable[] = { { SM_STATE_INITIALIZE, SM_STATE_RUNNING, SM_EVENT_INITIALIZE_OK },
                                                { SM_STATE_RUNNING, SM_STATE_SLEEP, SM_EVENT_END_RUNNING },
                                                { SM_STATE_SLEEP, SM_STATE_RUNNING, SM_EVENT_END_SLEEP },
                                                { SM_STATE_RUNNING, SM_STATE_WAIT_FOR_SEND, SM_EVENT_START_SENDING },
                                                { SM_STATE_WAIT_FOR_SEND, SM_STATE_SLEEP, SM_EVENT_END_RUNNING } };
SmFunctions_TypeDef Function[]              = { { SM_InitializeFunction }, { SM_RunningFunction }, { SM_WaitForSendFunction }, { SM_SleepFunction } };
Sm_TypeDef SmPtr                            = { 0 };
bh1750_t Bh                                 = { 0 };
#ifndef DEBUG_SWDIO
MAX_TypeDef MAX = { 0 };
#endif
void SM_MainFunction()
{
#ifndef DEBUG_SWDIO
   if(MAX.Initialize == MAX_INITIALIZE)
   {
      MAX_Handle();
   }
#endif
   if(HAL_GetTick() - SmPtr.LastTick > 10)
   {
      SM_ChangeState();
      SmPtr.LastTick = HAL_GetTick();
      if(Function[SmPtr.State].SmFunction != NULL)
      {
         Function[SmPtr.State].SmFunction();
      }
   }
}
static void SM_ChangeState(void)
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
   SmPtr.NewEvent = SM_EVENT_NOTHING;
}
static void SM_InitializeFunction(void)
{

   MAX_Init(&MAX, MAX_BS);
   MAX_RegisterCommandFunction(MAX_TEST, MAX_CommandTestFunction);
   MAX_RegisterCommandFunction(MAX_START_MEASURMENT, MAX_CommandStartMeasurmentFunction);
   MAX_RegisterCommandFunction(MAX_GO_TO_DEEP_SLEEP, MAX_CommandGoToDeepSleepFunction);

   bh1750_Init(&Bh, &hi2c2, 35, One_Time_H_Resolution_Mode);
   SmPtr.NewEvent = SM_EVENT_INITIALIZE_OK;
}
static void SM_RunningFunction(void)
{
   if(MAX.State == MAX_STATE_IDLE)
   {
      if(SmPtr.MeasurmentFlag == SM_FLAG_SET)
      {
         SmPtr.MeasurmentFlag = SM_FLAG_RESET;
         SmPtr.Brightness     = bh1750_ReadLuxOneTime(&Bh);
         SmPtr.NewEvent       = SM_EVENT_START_SENDING;
         MAX_SendData(MAX_ODWS, MAX_DATA, (uint8_t *)&SmPtr.Brightness, 2);
      }
      else
      {
         SmPtr.NewEvent = SM_EVENT_END_RUNNING;
      }
   }
}
static void SM_WaitForSendFunction(void)
{
   if(MAX.State == MAX_STATE_IDLE)
   {
      SmPtr.NewEvent = SM_EVENT_END_RUNNING;
   }
}
static void SM_SleepFunction(void)
{

   if(SmPtr.DeepSleepFlag == SM_FLAG_SET)
   {
      SmPtr.DeepSleepFlag = SM_FLAG_RESET;
      // HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
      SmPtr.NewEvent = SM_EVENT_END_SLEEP;
   }
   else
   {
      // HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
      SmPtr.NewEvent = SM_EVENT_END_SLEEP;
   }
}
void MAX_CommandTestFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart)
{
#ifndef DEBUG_SWDIO
   uint8_t Temp = MAX_OK;
   MAX_SendData(MAX_ODWS, MAX_MESSAGE, &Temp, 1);
#endif
}
void MAX_CommandStartMeasurmentFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart)
{
   SmPtr.MeasurmentFlag = SM_FLAG_SET;
}
void MAX_CommandGoToDeepSleepFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart)
{
}


