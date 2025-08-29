/*
 * State_Machine_GIT.h
 *
 *  Created on: Apr 4, 2023
 *      Author: JuliaUruelSanz
 */

#ifndef INC_STATE_MACHINE_GIT_H_
#define INC_STATE_MACHINE_GIT_H_

#include "tc358870.h"

void RS1(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS2(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS3(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS4(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS5(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS_DO(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void LCD_Init(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void int_status_check(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void tc358870_HDMI_TimChk(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);


#endif /* INC_STATE_MACHINE_GIT_H_ */
