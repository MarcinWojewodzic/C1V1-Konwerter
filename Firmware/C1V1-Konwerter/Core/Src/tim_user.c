/*
 * tim_user.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Marcin
 */
#include "main.h"
#include "tim_user.h"
uint16_t TIM_GetTick()
{
	return TIM17->CNT;
}

