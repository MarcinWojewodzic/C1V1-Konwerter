/*
 * supp.c
 *
 *  Created on: 3 wrz 2022
 *      Author: Marcin
 */
#include "main.h"
#include "supp.h"
uint16_t TIM_GetTick()
{
	return TIM17->CNT;
}

