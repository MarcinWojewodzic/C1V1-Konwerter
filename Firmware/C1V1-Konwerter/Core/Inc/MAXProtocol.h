/*
 * max.h
 *
 *  Created on: 24 paź 2022
 *      Author: M
 */

#ifndef INC_MAX_H_
#define INC_MAX_H_
#include "main.h"
#define MAX_TRANSITION_TABLE_SIZE sizeof(MAXTransitionTable) / sizeof(MAXTransitionTable_TypeDef)
#define MAX_COMMAND_CNT           3
#define MAX_MESSAGE_CNT           4
typedef enum
{
   MAX_BS   = 0x01,
   MAX_ODWS = 0x02,
   MAX_IDWS = 0x03
} MAXDeviceID_TypeDef;
typedef enum
{
   MAX_TEMPERATURE_AHT_15          = 0x01,
   MAX_HUMIDITI_AHT_15             = 0x02,
   MAX_TEMPERATURE_DS18B20         = 0x03,
   MAX_TEMPERATURE_INTERNAL        = 0x04,
   MAX_BATTERY_LEVEL               = 0x05,
   MAX_BRIGHTNESS                  = 0x06,
   MAX_EXTERNAL_MODULE_TEMPERATURE = 0x07,
   MAX_BATTERY_STATE               = 0x08,
   MAX_AIR_POLLUTION_PM1           = 0x09,
   MAX_AIR_POLLUTION_PM25          = 0x0a,
   MAX_AIR_POLLUTION_PM10          = 0x0b
} MAXParameters_TypeDef;
typedef enum
{
   MAX_TEMPERATURE_AHT_15_SIZE          = 0x04,
   MAX_HUMIDITI_AHT_15_SIZE             = 0x04,
   MAX_TEMPERATURE_DS18B20_SIZE         = 0x04,
   MAX_TEMPERATURE_INTERNAL_SIZE        = 0x04,
   MAX_BATTERY_LEVEL_SIZE               = 0x04,
   MAX_BRIGHTNESS_SIZE                  = 0x02,
   MAX_EXTERNAL_MODULE_TEMPERATURE_SIZE = 0x04,
   MAX_BATTERY_STATE_SIZE               = 0x01,
   MAX_AIR_POLLUTION_PM1_SIZE           = 0x02,
   MAX_AIR_POLLUTION_PM25_SIZE          = 0x02,
   MAX_AIR_POLLUTION_PM10_SIZE          = 0x02,
} MAXSizeParameters_TypeDef;
typedef enum
{
   MAX_TEST             = 0x01,
   MAX_START_MEASURMENT = 0x02,
   MAX_GO_TO_DEEP_SLEEP = 0x03
} MAXCommands_TypeDef;
typedef enum
{
   MAX_ERROR       = 0x01,
   MAX_CRC_ERROR   = 0x02,
   MAX_LOW_BATTERY = 0x03,
   MAX_OK          = 0x04
} MAXMessage_TypeDef;
typedef enum
{
   MAX_COMMAND = 0x01,
   MAX_DATA    = 0x02,
   MAX_MESSAGE = 0x03
} MAXMessageType_TypeDef;
typedef enum
{
   MAX_ERROR_SIZE       = 0x00,
   MAX_CRC_ERROR_SIZE   = 0x00,
   MAX_LOW_BATTERY_SIZE = 0x04,
   MAX_OK_SIZE          = 0x00
} MAXMessageDataSize_TypeDef;
typedef enum
{
   MAX_TEST_SIZE             = 0x00,
   MAX_START_MEASURMENT_SIZE = 0x00,
   MAX_GO_TO_DEEP_SLEEP_SIZE = 0x02
} MAXCommandDataSize_TypeDef;
typedef enum
{
   MAX_STATE_INITIALIZE = 0x00,
   MAX_STATE_IDLE,
   MAX_STATE_PARSE,
   MAX_STATE_RUNNING,
   MAX_STATE_SEND,
   MAX_STATE_WAIT_FOR_RESPONSE,
   MAX_STATE_PARSE_RESPONSE
} MAXState_TypeDef;
typedef enum
{
   MAX_EVENT_NOTHING = 0x00,
   MAX_EVENT_NEW_DATA,
   MAX_EVENT_END_INITIALIZE,
   MAX_EVENT_ERROR,
   MAX_EVENT_DATA_OK,
   MAX_EVENT_WAIT_FOR_RESPONSE,
   MAX_EVENT_SEND
} MAXEvent_TypeDef;
typedef enum
{
   MAX_NOT_INITIALIZE = 0x00,
   MAX_INITIALIZE
} MAXInitialize_TypeDef;
typedef enum
{
   MAX_NEW_DATA_FLAG_RESET = 0x00,
   MAX_NEW_DATA_FLAG_SET
} MAXNewDataFlag_TypeDef;
typedef enum
{
   MAX_SEND_FLAG_RESET,
   MAX_SEND_FLAG_SET
} MAXSendFlag_TypeDef;
typedef struct
{
   MAXState_TypeDef Source;
   MAXState_TypeDef Destination;
   MAXEvent_TypeDef Event;
} MAXTransitionTable_TypeDef;
typedef struct
{
   MAXState_TypeDef State;
   MAXEvent_TypeDef NewEvent;
   MAXState_TypeDef OldSate;
   MAXInitialize_TypeDef Initialize;
   volatile MAXNewDataFlag_TypeDef NewDataFlag;
   MAXDeviceID_TypeDef DeviceType;
   uint32_t DataSize;
   MAXDeviceID_TypeDef SourceMessage;
   MAXSendFlag_TypeDef SendFlag;
   uint32_t Cnt;
   uint32_t LastTick;
   uint32_t DataTransmitSize;
} MAX_TypeDef;
typedef struct
{
   void (*MAXFunction)(void);
} MAXFunctions_TypeDef;
typedef struct
{
   void (*MAXCommandFunction)(uint8_t *, uint32_t, uint32_t);
} MAXCommandFunctions_TypeDef;
typedef struct
{
   void (*MAXDataFunction)(uint8_t *, uint32_t, uint32_t);
} MAXDataFunctions_TypeDef;
typedef struct
{
   void (*MAXMessageFunction)(uint8_t *, uint32_t, uint32_t);
} MAXMessageFunctions_TypeDef;
void MAX_Handle(void);
void MAX_Init(MAX_TypeDef *RadioProtocol, MAXDeviceID_TypeDef Device);
void MAX_RegisterCommandFunction(MAXCommands_TypeDef Command, void (*Callback)(uint8_t *, uint32_t, uint32_t));
void MAX_RegisterDataFunction(void (*Callback)(uint8_t *, uint32_t, uint32_t));
void MAX_RegisterMessageFunction(MAXMessage_TypeDef Message, void (*Callback)(uint8_t *, uint32_t, uint32_t));
void MAX_InterruptTask(void);
void MAX_SendData(MAXDeviceID_TypeDef Destination, MAXMessageType_TypeDef Type, uint8_t *Data, uint32_t Length);


#endif /* INC_MAX_H_ */
