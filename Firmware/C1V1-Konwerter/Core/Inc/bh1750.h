/*
 * bh1750.h
 *
 *  Created on: May 26, 2022
 *      Author: Marcin
 */

#ifndef INC_BH1750_H_
#define INC_BH1750_H_
#define bh1750_PowerDown 0b00000000
#define bh1750_PowerOn 0b00000001
#define bh1750_Reset 0b00000111
typedef enum
{
	Continuously_H_Resolution_Mode=0b00010000,
	Continuously_H_Resolution_Mode2=0b00010001,
	Continuously_L_Resolution_Mode=0b00010011,
	One_Time_H_Resolution_Mode=0b00100000,
	One_Time_H_Resolution_Mode2=0b00100001,
	One_Time_L_Resolution_Mode=0b00100011
}bh1750State_t;

typedef struct
{
	I2C_HandleTypeDef *bh_i2c;
	uint8_t addr;
	bh1750State_t state;
}bh1750_t;
void bh1750_Init(bh1750_t *bh,I2C_HandleTypeDef* i2c,uint8_t addres,bh1750State_t s);
uint16_t bh1750_ReadLuxOneTime(bh1750_t *bh);
#endif /* INC_BH1750_H_ */
