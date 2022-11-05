/*
 * max.c
 *
 *  Created on: 24 paź 2022
 *      Author: M
 */
#include "MAXProtocol.h"
#include "MAX485.h"
#include "crc.h"
#include "main.h"
#include "stdio.h"
uint8_t MAXDataRecive[100]   = { 0 };
uint8_t MAXDataTransmit[100] = { 0 };
static MAX_TypeDef *MAX;
static void MAX_ChangeState(void);
static void MAX_InitializeFunction(void);
static void MAX_IdleFunction(void);
static void MAX_ParseFunction(void);
static void MAX_RunningFunction(void);
static void MAX_SendFunction(void);
static void MAX_WaitForResponseFunction(void);
static void MAX_ParseResponseFunction(void);
static void MAX_SendResponseFunction(MAXMessageType_TypeDef Response);
void MAX_SendData(MAXDeviceID_TypeDef Destination, MAXMessageType_TypeDef Type, uint8_t *Data, uint32_t Length);
static MAXTransitionTable_TypeDef MAXTransitionTable[] = { { MAX_STATE_INITIALIZE, MAX_STATE_IDLE, MAX_EVENT_END_INITIALIZE },
                                                           { MAX_STATE_IDLE, MAX_STATE_PARSE, MAX_EVENT_NEW_DATA },
                                                           { MAX_STATE_PARSE, MAX_STATE_IDLE, MAX_EVENT_ERROR },
                                                           { MAX_STATE_PARSE, MAX_STATE_RUNNING, MAX_EVENT_DATA_OK },
                                                           { MAX_STATE_RUNNING, MAX_STATE_IDLE, MAX_EVENT_NOTHING },
                                                           { MAX_STATE_IDLE, MAX_STATE_SEND, MAX_EVENT_SEND },
                                                           { MAX_STATE_SEND, MAX_STATE_WAIT_FOR_RESPONSE, MAX_EVENT_WAIT_FOR_RESPONSE },
                                                           { MAX_STATE_WAIT_FOR_RESPONSE, MAX_STATE_SEND, MAX_EVENT_ERROR },
                                                           { MAX_STATE_WAIT_FOR_RESPONSE, MAX_STATE_PARSE_RESPONSE, MAX_EVENT_NEW_DATA },
                                                           { MAX_STATE_PARSE_RESPONSE, MAX_STATE_SEND, MAX_EVENT_ERROR },
                                                           { MAX_STATE_PARSE_RESPONSE, MAX_STATE_IDLE, MAX_EVENT_DATA_OK },
                                                           { MAX_STATE_SEND, MAX_STATE_IDLE, MAX_EVENT_ERROR } };
MAXFunctions_TypeDef MAXFunction[]
    = { { MAX_InitializeFunction },      { MAX_IdleFunction },         { MAX_ParseFunction }, { MAX_RunningFunction }, { MAX_SendFunction },
        { MAX_WaitForResponseFunction }, { MAX_ParseResponseFunction } };
MAXCommandFunctions_TypeDef MAXCommandFunction[MAX_COMMAND_CNT];
MAXDataFunctions_TypeDef MAXDataFunctions;
MAXMessageFunctions_TypeDef MAXMessageFunction[MAX_MESSAGE_CNT];
void MAX_Handle(void)
{
   MAX_ChangeState();
   if(MAXFunction[MAX->State].MAXFunction != NULL)
   {
      MAXFunction[MAX->State].MAXFunction();
   }
}
void MAX_Init(MAX_TypeDef *RadioProtocol, MAXDeviceID_TypeDef Device)
{
   MAX             = RadioProtocol;
   MAX->Initialize = MAX_INITIALIZE;
   MAX->DeviceType = Device;
   for(int i = 0; i < MAX_COMMAND_CNT; i++)
   {
      MAXCommandFunction[i].MAXCommandFunction = NULL;
   }
   for(int i = 0; i < MAX_MESSAGE_CNT; i++)
   {
      MAXMessageFunction[i].MAXMessageFunction = NULL;
   }
   MAXDataFunctions.MAXDataFunction = NULL;
   MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
   MAX485_Init(MAX);
}
static void MAX_ChangeState(void)
{
   for(int i = 0; i < MAX_TRANSITION_TABLE_SIZE; i++)
   {
      if(MAX->State == MAXTransitionTable[i].Source && MAX->NewEvent == MAXTransitionTable[i].Event)
      {
         MAX->State    = MAXTransitionTable[i].Destination;
         MAX->NewEvent = MAX_EVENT_NOTHING;
         return;
      }
   }
   MAX->NewEvent = MAX_EVENT_NOTHING;
}
void MAX_RegisterCommandFunction(MAXCommands_TypeDef Command, void (*Callback)(uint8_t *, uint32_t, uint32_t))
{
   MAXCommandFunction[Command - 1].MAXCommandFunction = Callback;
}
void MAX_RegisterDataFunction(void (*Callback)(uint8_t *, uint32_t, uint32_t))
{
   MAXDataFunctions.MAXDataFunction = Callback;
}
void MAX_RegisterMessageFunction(MAXMessage_TypeDef Message, void (*Callback)(uint8_t *, uint32_t, uint32_t))
{
   MAXMessageFunction[Message - 1].MAXMessageFunction = Callback;
}
void MAX_InterruptTask(void)
{
   MAX->NewDataFlag = MAX_NEW_DATA_FLAG_SET;
}
void MAX_SendData(MAXDeviceID_TypeDef Destination, MAXMessageType_TypeDef Type, uint8_t *Data, uint32_t Length)
{
   MAXDataTransmit[0] = Destination;
   MAXDataTransmit[1] = MAX->DeviceType;
   MAXDataTransmit[2] = Type;
   for(int i = 0; i < Length; i++)
   {
      MAXDataTransmit[i + 3] = Data[i];
   }
   uint32_t crc                    = Crc(CRC_INITIAL_VALUE, 3 + Length, MAXDataTransmit);
   MAXDataTransmit[3 + Length]     = ((crc >> 24) & 0xff);
   MAXDataTransmit[3 + Length + 1] = ((crc >> 16) & 0xff);
   MAXDataTransmit[3 + Length + 2] = ((crc >> 8) & 0xff);
   MAXDataTransmit[3 + Length + 3] = (crc & 0xff);
   MAX->SendFlag                   = MAX_SEND_FLAG_SET;
   MAX->DataTransmitSize           = 3 + Length + 4;
}
static void MAX_SendResponseFunction(MAXMessageType_TypeDef Response)
{
   //HAL_Delay(200);
   MAXDataTransmit[0] = MAX->SourceMessage;
   MAXDataTransmit[1] = MAX->DeviceType;
   MAXDataTransmit[2] = MAX_MESSAGE;
   MAXDataTransmit[3] = Response;
   uint32_t crc       = Crc(CRC_INITIAL_VALUE, 4, MAXDataTransmit);
   MAXDataTransmit[4] = ((crc >> 24) & 0xff);
   MAXDataTransmit[5] = ((crc >> 16) & 0xff);
   MAXDataTransmit[6] = ((crc >> 8) & 0xff);
   MAXDataTransmit[7] = (crc & 0xff);
   MAX485_TransmitData(MAXDataTransmit, 8);
}
static void MAX_InitializeFunction(void)
{
   MAX->NewEvent = MAX_EVENT_END_INITIALIZE;
}
static void MAX_IdleFunction(void)
{
   if(MAX->NewDataFlag == MAX_NEW_DATA_FLAG_SET)
   {
      MAX->NewDataFlag = MAX_NEW_DATA_FLAG_RESET;
      MAX->NewEvent    = MAX_EVENT_NEW_DATA;
   }
   else if(MAX->SendFlag == MAX_SEND_FLAG_SET)
   {
      MAX->SendFlag = MAX_SEND_FLAG_RESET;
      MAX->NewEvent = MAX_EVENT_SEND;
      MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
   }
}
static void MAX_ParseFunction(void)
{
   uint32_t MessageCRC = 0;
   MAX->SourceMessage  = MAXDataRecive[1];
   if(MAXDataRecive[0] != MAX->DeviceType)
   {
      MAX->NewEvent = MAX_EVENT_ERROR;
      MAX_SendResponseFunction(MAX_ERROR);
      MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
   }
   else
   {
      if(MAX->DataSize != 0)
      {
         MessageCRC = (((uint32_t)MAXDataRecive[MAX->DataSize - 4] << 24) | ((uint32_t)MAXDataRecive[MAX->DataSize - 3] << 16)
                       | ((uint32_t)MAXDataRecive[MAX->DataSize - 2] << 8) | ((uint32_t)MAXDataRecive[MAX->DataSize - 1]));
         if(MessageCRC == Crc(CRC_INITIAL_VALUE, MAX->DataSize - 4, MAXDataRecive))
         {
            MAX->NewEvent = MAX_EVENT_DATA_OK;
            MAX_SendResponseFunction(MAX_OK);
         }
         else
         {
            if(RepareMessage(MessageCRC, MAXDataRecive, MAX->DataSize) == CRC_OK)
            {
               MAX->NewEvent = MAX_EVENT_DATA_OK;
               MAX_SendResponseFunction(MAX_OK);
            }
            else
            {
               MAX->NewEvent = MAX_EVENT_ERROR;
               MAX_SendResponseFunction(MAX_CRC_ERROR);
               MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
            }
         }
      }
   }
}
static void MAX_RunningFunction(void)
{
   switch(MAXDataRecive[2])
   {
      case MAX_COMMAND:
      {
         if(MAXCommandFunction[MAXDataRecive[3] - 1].MAXCommandFunction != NULL)
         {
            MAXCommandFunction[MAXDataRecive[3] - 1].MAXCommandFunction(MAXDataRecive, MAX->DataSize, 4);
         }
         break;
      }
      case MAX_DATA:
      {
         if(MAXDataFunctions.MAXDataFunction != NULL)
         {
            MAXDataFunctions.MAXDataFunction(MAXDataRecive, MAX->DataSize, 4);
         }
         break;
      }
      case MAX_MESSAGE:
      {
         if(MAXMessageFunction[MAXDataRecive[3] - 1].MAXMessageFunction != NULL)
         {
            MAXMessageFunction[MAXDataRecive[3] - 1].MAXMessageFunction(MAXDataRecive, MAX->DataSize, 4);
         }
         break;
      }
      default:
      {
         break;
      }
   }
   MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
}
static void MAX_SendFunction(void)
{
   if(MAX->Cnt < 5)
   {
      //HAL_Delay(200);
      MAX485_TransmitData(MAXDataTransmit, MAX->DataTransmitSize);
      MAX->Cnt++;
      MAX->NewEvent = MAX_EVENT_WAIT_FOR_RESPONSE;
      MAX->LastTick = HAL_GetTick();
   }
   else
   {
      MAX->Cnt      = 0;
      MAX->NewEvent = MAX_EVENT_ERROR;
      MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
   }
}
static void MAX_WaitForResponseFunction(void)
{
   if(HAL_GetTick() - MAX->LastTick > 2000)
   {
      MAX->NewEvent = MAX_EVENT_ERROR;
   }
   else if(MAX->NewDataFlag == MAX_NEW_DATA_FLAG_SET)
   {
      MAX->NewDataFlag = MAX_NEW_DATA_FLAG_RESET;
      MAX->NewEvent    = MAX_EVENT_NEW_DATA;
   }
}
static void MAX_ParseResponseFunction(void)
{
   uint32_t MessageCRC = (((uint32_t)MAXDataRecive[MAX->DataSize - 4] << 24) | ((uint32_t)MAXDataRecive[MAX->DataSize - 3] << 16)
                          | ((uint32_t)MAXDataRecive[MAX->DataSize - 2] << 8) | ((uint32_t)MAXDataRecive[MAX->DataSize - 1]));
   if(MessageCRC == Crc(CRC_INITIAL_VALUE, MAX->DataSize - 4, MAXDataRecive))
   {
      if(MAXDataRecive[0] == MAX->DeviceType && MAXDataRecive[2] == MAX_MESSAGE)
      {
         if(MAXDataRecive[3] == MAX_OK)
         {
            MAX->NewEvent = MAX_EVENT_DATA_OK;
            MAX->Cnt      = 0;
            MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
         }
         else
         {
            MAX->NewEvent = MAX_EVENT_ERROR;
            MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
         }
      }
      else
      {
         MAX->NewEvent = MAX_EVENT_ERROR;
         MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
      }
   }
   else if(RepareMessage(MessageCRC, MAXDataRecive, MAX->DataSize) == CRC_OK)
   {
      if(MAXDataRecive[0] == MAX->DeviceType && MAXDataRecive[2] == MAX_MESSAGE)
      {
         if(MAXDataRecive[3] == MAX_OK)
         {
            MAX->NewEvent = MAX_EVENT_DATA_OK;
            MAX->Cnt      = 0;
            MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
         }
         else
         {
            MAX->NewEvent = MAX_EVENT_ERROR;
            MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
         }
      }
      else
      {
         MAX->NewEvent = MAX_EVENT_ERROR;
         MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
      }
   }
   else
   {
      MAX485_ReciveToIdleDMA(MAXDataRecive, sizeof(MAXDataRecive));
      MAX->NewEvent = MAX_EVENT_ERROR;
   }
}
