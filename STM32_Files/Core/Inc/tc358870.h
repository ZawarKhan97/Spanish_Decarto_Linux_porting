/*
 * tc3358870.h
 *
 *  Created on: 27 feb. 2023
 *      Author: JuliaUruelSanz */

#ifndef INC_TC358870_H_
#define INC_TC358870_H_

#include "stm32l4xx_hal.h"

#define ADDR_TOSHIBA 0x1E //Data sheet 0x1F- if Int pulled Up and 0x0F if not
uint8_t i2c1_uh2cd_write8(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1,uint16_t addr,uint8_t dt);
uint8_t i2c1_uh2cd_write16(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1,uint16_t addr,uint16_t dt);
uint8_t i2c1_uh2cd_write32(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1,uint16_t addr,uint32_t dt);
uint8_t i2c1_uh2cd_read8(I2C_HandleTypeDef *hi2c1,uint16_t addr);
uint16_t i2c1_uh2cd_read16(I2C_HandleTypeDef *hi2c1,uint16_t addr);
uint32_t i2c1_uh2cd_read32(I2C_HandleTypeDef *hi2c1,uint16_t addr);


void data_send_COM_Info(UART_HandleTypeDef *huart, uint32_t data, uint16_t addr, uint8_t error);

#endif /* INC_TC358870_H_ */
