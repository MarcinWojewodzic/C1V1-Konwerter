/*
 * bh1750.c
 *
 *  Created on: May 26, 2022
 *      Author: Marcin
 */
#include "main.h"
#include "bh1750.h"
void bh1750_TransmitData(bh1750_t *bh,uint8_t *data,uint8_t size)
{
	HAL_I2C_Master_Transmit(bh->bh_i2c, (bh->addr<<1), data, size, 1000);
}
void bh1750_ReceiveData(bh1750_t *bh,uint8_t *data,uint8_t size)
{
	HAL_I2C_Master_Receive(bh->bh_i2c, (bh->addr<<1), data, size, 1000);
}
void bh1750_ChangeState(bh1750_t *bh,bh1750State_t s)
{
	if(s==Continuously_H_Resolution_Mode||s==Continuously_H_Resolution_Mode2||s==Continuously_L_Resolution_Mode)
	bh1750_TransmitData(bh,&s,1);
	bh->state=s;
}
void bh1750_SendStartMeasurment(bh1750_t *bh)
{
	if(bh->state==One_Time_H_Resolution_Mode||bh->state==One_Time_H_Resolution_Mode2||bh->state==One_Time_L_Resolution_Mode)
	{
		bh1750_TransmitData(bh,&bh->state,1);
	}
}
uint16_t bh1750_ReadMeasurment(bh1750_t *bh)
{
	uint8_t data[2];
	bh1750_ReceiveData(bh, data, 2);
	return ((data[0]<<8)|(data[1]));
}
uint16_t bh1750_ReadLuxOneTime(bh1750_t *bh)
{
	bh1750_SendStartMeasurment(bh);
	HAL_Delay(200);
	uint16_t rowMeasurment=bh1750_ReadMeasurment(bh);
	return rowMeasurment;
}
void bh1750_Init(bh1750_t *bh,I2C_HandleTypeDef* i2c,uint8_t addres,bh1750State_t s)
{
	bh->bh_i2c=i2c;
	bh->addr=addres;
	if(s!=0)
	bh1750_ChangeState(bh, s);
	bh->state=s;
}

