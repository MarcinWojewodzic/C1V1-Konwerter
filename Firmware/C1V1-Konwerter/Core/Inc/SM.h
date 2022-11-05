/*
 * SM.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */

#ifndef INC_SM_H_
#define INC_SM_H_
#define TRANSITION_TABLE_SIZE sizeof(TransitionTable) / sizeof(SmTransitionTable_TypeDef)
#define COMMANDS_TABLE_SIZE   sizeof(LsCommands) / sizeof(LsCommands_TypeDef)
#include "main.h"
//#define DEBUG_SWDIO
typedef enum
{
   SM_STATE_INITIALIZE,
   SM_STATE_RUNNING,
   SM_STATE_WAIT_FOR_SEND,
   SM_STATE_SLEEP,
} SmState_TypeDef;
typedef enum
{
   SM_EVENT_NOTHING,
   SM_EVENT_INITIALIZE_OK,
   SM_EVENT_END_RUNNING,
   SM_EVENT_END_SLEEP,
   SM_EVENT_START_SENDING
} SmEvent_TypeDef;
typedef enum
{
   SM_FLAG_RESET,
   SM_FLAG_SET
} SmFlag_TypeDef;
typedef struct
{
   SmState_TypeDef Source;
   SmState_TypeDef Destination;
   SmEvent_TypeDef Event;
} SmTransitionTable_TypeDef;
typedef struct
{
   void (*SmFunction)(void);
} SmFunctions_TypeDef;
typedef struct
{
   char *Commands;
   uint16_t SizeCommands;
} LsCommands_TypeDef;
typedef struct
{
   uint32_t LastTick;
   SmState_TypeDef State;
   SmEvent_TypeDef NewEvent;
   SmFlag_TypeDef MeasurmentFlag;
   SmFlag_TypeDef DeepSleepFlag;
   uint16_t Brightness;
} Sm_TypeDef;
void SM_MainFunction();
#endif /* INC_SM_H_ */
