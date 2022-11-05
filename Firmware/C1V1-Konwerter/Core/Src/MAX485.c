/*
 * MAX485.c
 *
 *  Created on: Oct 29, 2022
 *      Author: M
 */

#include "MAX485.h"
#include "MAXProtocol.h"
#include "main.h"
#include "usart.h"
static MAX_TypeDef *MAX;
static void MAX485_ListeningMode(void)
{
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, 0);
}
static void MAX485_TransmitMode(void)
{
   HAL_GPIO_WritePin(MAX485_Selector_GPIO_Port, MAX485_Selector_Pin, 1);
}
void MAX485_ReciveToIdleDMA(uint8_t *Data, uint16_t Length)
{
   MAX485_ListeningMode();
   HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Data, Length);
}
void MAX485_TransmitData(uint8_t *Data, uint16_t Length)
{
   MAX485_TransmitMode();
   __disable_irq();
   HAL_UART_Transmit(&huart1, Data, Length, 1000);
   __enable_irq();
   MAX485_ListeningMode();
}
void MAX485_Init(MAX_TypeDef *max)
{
   MAX = max;
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
   if(Size > 4 && Size < 101)
   {
      MAX->DataSize = Size;
      MAX_InterruptTask();
   }
}
