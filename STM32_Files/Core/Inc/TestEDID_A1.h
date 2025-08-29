
#ifndef INC_TestEDID_A1_H_
#define INC_TestEDID_A1_H_

#include "stm32l4xx_hal.h"

void TestEDID_A1(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS5_A1(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS3_A1(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);
void RS2_A1(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1);

#endif /* INC_TestEDID_A1_H_ */
