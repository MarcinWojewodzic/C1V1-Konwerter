/*
 * SM.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */

#ifndef INC_SM_H_
#define INC_SM_H_
#define TRANSITION_TABLE_SIZE sizeof(TransitionTable)/sizeof(SmTransitionTable_TypeDef)
#include "main.h"
typedef enum
{
	SM_STATE_INITIALIZE,
	SM_STATE_RUNNING,
	SM_STATE_SLEEP,
	SM_STATE_PARSE_UART,
	SM_STATE_DEBUG,
	SM_STATE_ERROR
} SmState_TypeDef;
typedef enum
{
	SM_EVENT_NOTHING,
	SM_EVENT_INITIALIZE_OK,
	SM_EVENT_ERROR,
	SM_EVENT_END_RUNNING,
	SM_EVENT_END_SLEEP,
	SM_EVENT_UART,
	SM_EVENT_DEBUG
} SmEvent_TypeDef;
typedef enum
{
	LS_LISTENING,
	LS_TRANSMIT
}LightSensorTransmit_Typedef;
typedef struct
{
	SmState_TypeDef Source;
	SmState_TypeDef Destination;
	SmEvent_TypeDef Event;
}SmTransitionTable_TypeDef;
typedef struct
{
	void(*SmFunction)(void);
}SmFunctions_TypeDef;
typedef struct
{
	uint16_t LastTick;
	SmState_TypeDef State;
	SmEvent_TypeDef NewEvent;
} Sm_TypeDef;
void SM_MainFunction();
#endif /* INC_SM_H_ */
