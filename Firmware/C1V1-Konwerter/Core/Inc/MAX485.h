/*
 * MAX485.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */

#ifndef INC_MAX485_H_
#define INC_MAX485_H_
#define MAX485_MAX_TIMEOUT 1000
typedef enum
{
	MAX485_LISTENING,
	MAX485_SENDING
} Max485State_TypeDef;
typedef struct
{
	Max485State_TypeDef State;
	UART_HandleTypeDef *Max485Uart;
	GPIO_TypeDef *Max485SelectorPort;
	uint16_t Max485SelectorPin;
} Max485_Typedef;
void Max485_SetStateListening(Max485_Typedef *Max);
void Max485_SetStateSending(Max485_Typedef *Max);
void Max485_StartListening(Max485_Typedef *Max, uint8_t *DataToRecive, uint16_t NumberDataToRecive);
void Max485_StartSending(Max485_Typedef *Max, uint8_t *DataToSend, uint16_t NumberDataToSend);
void Max485_Init(Max485_Typedef *Max, UART_HandleTypeDef *Uart, GPIO_TypeDef *MaxSelectorPort, uint16_t MaxSelectorPin);
#endif /* INC_MAX485_H_ */
