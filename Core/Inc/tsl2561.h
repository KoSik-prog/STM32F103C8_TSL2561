/*
 * gy2561.h
 *
 *  Created on: 19 maj 2019
 *      Author: kosik
 */
#include "main.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifndef TSL2561_H_
#define TSL2561_H_

#define TSL2561_REGISTER_CONTROL 		  (0x00) // Control/power register
#define TSL2561_REGISTER_TIMING 		  (0x01) // Integration time register
#define TSL2561_REGISTER_THRESHHOLDL_LOW  (0x02) // Interrupt low threshold low-byte
#define TSL2561_REGISTER_THRESHHOLDL_HIGH (0x03) // Interrupt low threshold high-byte
#define TSL2561_REGISTER_THRESHHOLDH_LOW  (0x04) // Interrupt high threshold low-byte
#define TSL2561_REGISTER_THRESHHOLDH_HIGH (0x05) // Interrupt high threshold high-byte
#define TSL2561_REGISTER_INTERRUPT 		  (0x06) // Interrupt settings
#define TSL2561_REGISTER_CRC 			  (0x08) // Factory use only
#define TSL2561_REGISTER_ID 			  (0x0A) // #define GY2561 identification setting
#define TSL2561_REGISTER_CHAN0_LOW 		  (0x0C) // Light data channel 0, low byte
#define TSL2561_REGISTER_CHAN0_HIGH       (0x0D) // Light data channel 0, high byte
#define TSL2561_REGISTER_CHAN1_LOW 		  (0x0E) // Light data channel 1, low byte
#define TSL2561_REGISTER_CHAN1_HIGH 	  (0x0F) // Light data channel 1, high byte

#define TSL2561_COMMAND_BIT       		  (0x80)
#define TSL2561_CLEAR_BIT         		  (0x40) //< Clears pending interrupt
#define TSL2561_WORD_BIT          		  (0x20) //< 1 = read/write word
#define TSL2561_BLOCK_BIT         		  (0x10) //< 1 = using block read/write

#define TSL2561_ON 						  (0x03)
#define TSL2561_OFF 					  (0x00)

#define TSL2561_GAIN					  (0x10)
#define TSL2561_MANUAL					  (0x08)
#define TSL2561_INTEG_13_7					  (0x00)
#define TSL2561_INTEG_101					  (0x01)
#define TSL2561_INTEG_402					  (0x02)
#define TSL2561_INTEG_OFF					  (0x03)

struct TSL2561 {
	I2C_HandleTypeDef *hi2c;
	uint8_t sensorAddress;
};

HAL_StatusTypeDef tsl2561_init(I2C_HandleTypeDef *hi2c, uint8_t sensorAddress, uint8_t integ);
float tsl2561_readLux(void);
HAL_StatusTypeDef tsl2561_off(void);
uint16_t tsl2561_readLight(void);
uint16_t tsl2561_readIr(void);

#endif /* TSL2561_H_ */
