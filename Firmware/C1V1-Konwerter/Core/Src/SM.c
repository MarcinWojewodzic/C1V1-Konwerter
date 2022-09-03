/*
 * SM.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */
#include "SM.h"

#include "MAX485.h"
#include "bh1750.h"
#include "main.h"
#include "stdio.h"
#include "tim_user.h"
static void SM_InitializeFunction();
static void SM_RunningFunction();
SmTransitionTable_TypeDef TransitionTable[] = { { SM_STATE_INITIALIZE, SM_STATE_RUNNING, SM_EVENT_INITIALIZE_OK }, {}, {}, {}, {} };
SmFunctions_TypeDef Function[]              = { { SM_InitializeFunction }, { SM_RunningFunction } };
Sm_TypeDef SmPtr                            = { 0 };
void SM_MainFunction()
{
   if(TIM_GetTick() - SmPtr.LastTick > 10)
   {
      if(Function[SmPtr.State].SmFunction != NULL)
      {
         Function[SmPtr.State].SmFunction();
      }
   }
}
void SM_ChangeState()
{
   for(int i = 0; i < TRANSITION_TABLE_SIZE; i++)
   {
      if(SmPtr.State == TransitionTable[i].Source && SmPtr.NewEvent == TransitionTable[i].Event)
      {
         SmPtr.State = TransitionTable[i].Destination;
      }
   }
}
static void SM_InitializeFunction()
{
}
static void SM_RunningFunction()
{
}
