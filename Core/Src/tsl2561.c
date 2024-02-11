/*
 * tsl2561.c
 *
 *  Created on: 10.02.2024
 *      Author: Marcin Kosela (KoSik)
 *		e-mail: kosik84@gmail.com
 *
 *	   version: 1.0
 */

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "tsl2561.h"

/* USER CODE BEGIN PV */
struct TSL2561 tsl2561;
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
static HAL_StatusTypeDef tsl2561_writeReg(uint8_t command, uint8_t data);
static HAL_StatusTypeDef tsl2561_readReg(uint8_t command, uint8_t *data, uint8_t length);
/* USER CODE END PFP */


/*
 * Init Function:
 * @param  hi2c - I2C handle pointer
 * @param  sensorAddress
 * @param  integ - integrate time
 * @retval HAL status
 * */
HAL_StatusTypeDef tsl2561_init(I2C_HandleTypeDef *hi2c, uint8_t sensorAddress, uint8_t integ){
	uint8_t data;
	tsl2561.hi2c = hi2c;
	tsl2561.sensorAddress = sensorAddress;

	tsl2561_writeReg(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_ON);
	tsl2561_writeReg(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, integ);
	tsl2561_readReg(TSL2561_COMMAND_BIT | TSL2561_REGISTER_ID, &data, 1);
	if(data==0x50){
		return HAL_OK;
	} else{
		return HAL_ERROR;
	}
}

/*
 * Read and calculate light in LUX:
 * @retval light value (LUX)
 * */
float tsl2561_readLux(void){
	float lux;
	uint16_t light = tsl2561_readLight(); //CH0
	uint16_t ir = tsl2561_readIr(); //CH1

	float checkVal = (float)ir/(float)light;
	if (0 < checkVal && checkVal <= 0.5) {
		float buf1 = pow((checkVal), 1.4);
		lux = (0.0304 * (float)light) - (0.062 * (float)light * buf1);
	} else if (0.5 < checkVal && checkVal <= 0.61){
		lux = (0.0224 * (float)light) - (0.031 * (float)ir);
	} else if (0.61 < checkVal && checkVal <= 0.8){
		lux = (0.0128 * (float)light) - (0.0153 * (float)ir);
	} else if (0.8 < checkVal && checkVal <= 1.3){
		lux = (0.00146 * (float)light) - (0.00112 * (float)ir);
	} else {
		lux = 0;
	}
	return lux;
}

/*
 * Read ADC Channel 0 Visible + IR light:
 * @retval light value
 * */
uint16_t tsl2561_readLight(void){
	uint8_t data[2];
	tsl2561_readReg(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CHAN0_LOW, &data[0], 2);
	return data[1]<<8 | data[0];
}

/*
 * Read ADC Channel 1 IR light:
 * @retval IR light value
 * */
uint16_t tsl2561_readIr(void){
	uint8_t data[2];
	tsl2561_readReg(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CHAN1_LOW, &data[0], 2);
	return data[1]<<8 | data[0];
}

/*
 * Turn OFF the sensor:
 * @retval light value
 * */
HAL_StatusTypeDef  tsl2561_off(void){
	return tsl2561_writeReg(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_OFF);
}

static HAL_StatusTypeDef tsl2561_writeReg(uint8_t command, uint8_t data){
	uint8_t wdata = data;
	return HAL_I2C_Mem_Write(tsl2561.hi2c, tsl2561.sensorAddress, command, 1, &wdata, 1, 100);
}

static HAL_StatusTypeDef tsl2561_readReg(uint8_t command, uint8_t *data, uint8_t length){
	return HAL_I2C_Mem_Read(tsl2561.hi2c, tsl2561.sensorAddress, command, 1, data, length, 100);
}
