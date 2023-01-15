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
#include "adc.h"
static void SM_ChangeState(void);
static void SM_InitializeFunction(void);
static void SM_RunningFunction(void);
static void SM_WaitForSendFunction(void);
static void SM_SleepFunction(void);
void MAX_CommandTestFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart);
void MAX_CommandStartMeasurmentFunction(uint8_t *Data, uint32_t DataSize, uint32_t DataStart);
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
#ifndef DEBUG_SWDIO
   MAX_Init(&MAX, MAX_BS);
   MAX_RegisterCommandFunction(MAX_TEST, MAX_CommandTestFunction);
   MAX_RegisterCommandFunction(MAX_START_MEASURMENT, MAX_CommandStartMeasurmentFunction);
#endif
   uint16_t *TempPtr = 0x1FFF75A8;
   SmPtr.TS_CAL1     = *TempPtr;
   TempPtr           = 0x1FFF75CA;
   SmPtr.TS_CAL2     = *TempPtr;
   bh1750_Init(&Bh, &hi2c2, 35, One_Time_H_Resolution_Mode);
   HAL_ADC_Start(&hadc1);
   HAL_ADC_PollForConversion(&hadc1, 1000);
   uint16_t data     = HAL_ADC_GetValue(&hadc1);
   SmPtr.MeasurmentFlag=SM_FLAG_SET;
   SmPtr.Temperature = (((130.0 - 30.0) / ((float)SmPtr.TS_CAL2 - (float)SmPtr.TS_CAL1)) * (data - (float)SmPtr.TS_CAL1)) + 30.0;
   SmPtr.NewEvent    = SM_EVENT_INITIALIZE_OK;
}
static void SM_RunningFunction(void)
{
#ifndef DEBUG_SWDIO
   if(MAX.State == MAX_STATE_IDLE)
   {
      if(SmPtr.MeasurmentFlag == SM_FLAG_SET)
      {
         SmPtr.MeasurmentFlag = SM_FLAG_RESET;
         SmPtr.Brightness     = bh1750_ReadLuxOneTime(&Bh);
         SmPtr.NewEvent       = SM_EVENT_START_SENDING;
         HAL_ADC_Start(&hadc1);
         HAL_ADC_PollForConversion(&hadc1, 1000);
         uint16_t data     = HAL_ADC_GetValue(&hadc1);
         SmPtr.Temperature = (((130.0 - 30.0) / ((float)SmPtr.TS_CAL2 - (float)SmPtr.TS_CAL1)) * (data - (float)SmPtr.TS_CAL1)) + 30.0;
         uint8_t Data[20];
         Data[0]          = MAX_BRIGHTNESS;
         Data[1]          = (SmPtr.Brightness >> 8) & 0xff;
         Data[2]          = (SmPtr.Brightness & 0xff);
         uint8_t *TempPtr = &SmPtr.Temperature;
         Data[3]          = MAX_EXTERNAL_MODULE_TEMPERATURE;
         Data[4]          = *TempPtr;
         TempPtr++;
         Data[5] = *TempPtr;
         TempPtr++;
         Data[6] = *TempPtr;
         TempPtr++;
         Data[7] = *TempPtr;
         MAX_SendData(MAX_ODWS, MAX_DATA, Data, 8);
         MAX_Handle();
      }
      else
      {
         SmPtr.NewEvent = SM_EVENT_END_RUNNING;
      }
   }
#endif
#ifdef DEBUG_SWDIO
   SmPtr.NewEvent = SM_EVENT_END_RUNNING;
#endif
}
static void SM_WaitForSendFunction(void)
{
#ifndef DEBUG_SWDIO
   if(MAX.State == MAX_STATE_IDLE)
   {
      SmPtr.NewEvent = SM_EVENT_END_RUNNING;
   }
#endif
#ifdef DEBUG_SWDIO
   SmPtr.NewEvent = SM_EVENT_END_RUNNING;
#endif
}
static void SM_SleepFunction(void)
{

   HAL_SuspendTick();
   HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
   HAL_ResumeTick();
   SmPtr.NewEvent = SM_EVENT_END_SLEEP;
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
