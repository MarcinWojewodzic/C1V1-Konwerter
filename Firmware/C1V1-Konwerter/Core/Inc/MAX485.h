/*
 * MAX485.h
 *
 *  Created on: Oct 29, 2022
 *      Author: M
 */

#ifndef INC_MAX485_H_
#define INC_MAX485_H_
#include "main.h"
#include "MAXProtocol.h"
void MAX485_ReciveToIdleDMA(uint8_t *Data, uint16_t Length);
void MAX485_TransmitData(uint8_t *Data, uint16_t Length);
void MAX485_Init(MAX_TypeDef *max);

#endif /* INC_MAX485_H_ */
