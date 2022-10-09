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
   SM_STATE_WAIT_FOR_MEASURMENT_IS_FINISHED,
   SM_STATE_SLEEP,
   SM_STATE_PARSE_UART,
   SM_STATE_DEBUG,
   SM_STATE_ERROR
} SmState_TypeDef;
typedef enum
{
   SM_EVENT_NOTHING,
   SM_EVENT_INITIALIZE_OK,
   SM_EVENT_START_CONVESION,
   SM_EVENT_END_RUNNING,
   SM_EVENT_END_SLEEP,
   SM_EVENT_UART,
   SM_EVENT_DEBUG,
   SM_EVENT_END_DEBUG,
   SM_EVENT_ERROR
} SmEvent_TypeDef;
typedef enum
{
   LS_LISTENING,
   LS_TRANSMIT
} LsTransmit_Typedef;
typedef enum
{
   LS_NO_DEBUG,
   LS_DEBUG_COMMUNICATION,
   LS_DEBUG_MEASURMENT,
   LS_DEBUG_STATUS_AND_PARAM,
   LS_DEBUG_ALL
} LsDebugFlag_TypeDef;
typedef enum
{
   LS_NO_UART_RECIVE,
   LS_UART_RECIVE
} LsUartFlag_TypeDef;
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
   LsDebugFlag_TypeDef DebugFlag;
   LsUartFlag_TypeDef UartFlag;
   int Brightness;
} Sm_TypeDef;
void SM_MainFunction();
#endif /* INC_SM_H_ */
