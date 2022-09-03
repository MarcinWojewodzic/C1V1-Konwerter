/*
 * MAX485.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */
#include "MAX485.h"
#include "main.h"
void Max485_SetStateListening(Max485_Typedef *Max)
{
   HAL_GPIO_WritePin(Max->Max485SelectorPort, Max->Max485SelectorPin, MAX485_LISTENING);
   Max->State = MAX485_LISTENING;
}
void Max485_SetStateSending(Max485_Typedef *Max)
{
   HAL_GPIO_WritePin(Max->Max485SelectorPort, Max->Max485SelectorPin, MAX485_SENDING);
   Max->State = MAX485_SENDING;
}
void Max485_StartListening(Max485_Typedef *Max, uint8_t *DataToRecive, uint16_t NumberDataToRecive)
{
   HAL_UARTEx_ReceiveToIdle_DMA(Max->Max485Uart, DataToRecive, NumberDataToRecive);
}
void Max485_StartSending(Max485_Typedef *Max, uint8_t *DataToSend, uint16_t NumberDataToSend)
{
   HAL_UART_Transmit(Max->Max485Uart, DataToSend, NumberDataToSend, MAX485_MAX_TIMEOUT);
}
void Max485_ListeningAfterTalk(Max485_Typedef *Max, uint8_t *DataToSend, uint16_t NumberDataToSend, uint8_t *DataToRecive,
                               uint16_t NumberDataToRecive)
{
   Max485_SetStateSending(Max);
   Max485_StartSending(Max, DataToSend, NumberDataToSend);
   Max485_SetStateListening(Max);
   Max485_StartListening(Max, DataToRecive, NumberDataToRecive);
}
void Max485_Init(Max485_Typedef *Max, UART_HandleTypeDef *Uart, GPIO_TypeDef *MaxSelectorPort, uint16_t MaxSelectorPin)
{
   Max->Max485Uart         = Uart;
   Max->Max485SelectorPin  = MaxSelectorPin;
   Max->Max485SelectorPort = MaxSelectorPort;
   Max485_SetStateListening(Max);
}
