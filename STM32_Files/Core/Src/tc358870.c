#include "tc358870.h"

uint8_t i2c1_uh2cd_write8(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1,uint16_t addr,uint8_t dt){
	uint8_t write_reg[3];
	uint32_t data;
	HAL_StatusTypeDef ret=0;
	write_reg[0]=addr>>8;
	write_reg[1]=addr&0XFF;
	write_reg[2]=dt;
	ret=HAL_I2C_Master_Transmit(hi2c1, ADDR_TOSHIBA, write_reg, sizeof(write_reg),HAL_MAX_DELAY);
	while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY){HAL_Delay(100);}
	//HAL_Delay(10);
    data=i2c1_uh2cd_read8(hi2c1,addr);
    data_send_COM_Info(huart,data,addr,(uint8_t)ret);
    if (data==dt){
    	return 0;}
    return 1;
}

uint8_t i2c1_uh2cd_write16(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1,uint16_t addr,uint16_t dt){
	uint8_t write_reg[4];
	uint32_t data;
	HAL_StatusTypeDef ret=0;
	write_reg[0]=addr>>8;
	write_reg[1]=addr&0XFF;
	write_reg[2]=dt&0XFF;
	write_reg[3]=(dt>>8);
	ret=HAL_I2C_Master_Transmit(hi2c1, ADDR_TOSHIBA, write_reg, sizeof(write_reg),HAL_MAX_DELAY);
	while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY){HAL_Delay(100);}
	//HAL_I2C_DeInit(hi2c1);
	//HAL_I2C_Init(hi2c1);
	//HAL_Delay(100);
	if(addr!=0x0504){
	data=i2c1_uh2cd_read16(hi2c1,addr);
	if (data!=dt){
	    	return 1;}}
	//data_send_COM_Info(huart,data,addr,(uint8_t)ret);
	return 0;
}

uint8_t i2c1_uh2cd_write32(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1,uint16_t addr,uint32_t dt){
	uint8_t write_reg[6];
	uint32_t data;
	HAL_StatusTypeDef ret=0;
	write_reg[0]=addr>>8;
	write_reg[1]=addr&0XFF;
	write_reg[2]=(((dt&0XFFFFFFFF)&0XFFFF)& 0XFF);
	write_reg[3]=(((dt&0XFFFFFFFF)&0XFFFF)>>8);
	write_reg[4]=((dt&0XFFFFFFFF)>>8>>8);
	write_reg[5]=(dt>>8>>8>>8);
	ret=HAL_I2C_Master_Transmit(hi2c1, ADDR_TOSHIBA, write_reg, sizeof(write_reg),HAL_MAX_DELAY);
	while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY){HAL_Delay(1);}
	data=i2c1_uh2cd_read32(hi2c1,addr);
	//data_send_COM_Info(huart,data,addr,(uint8_t)ret);
	if (data==dt){
		  return 0;}
    return 1;
}

uint8_t i2c1_uh2cd_read8(I2C_HandleTypeDef *hi2c1,uint16_t addr){
	uint8_t temp[2];
	HAL_StatusTypeDef ret=0;
	ret=HAL_I2C_Mem_Read(hi2c1,ADDR_TOSHIBA,addr,I2C_MEMADD_SIZE_16BIT,temp,1,HAL_MAX_DELAY);
	while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY){HAL_Delay(1);}

	return temp[0];
}
uint16_t i2c1_uh2cd_read16(I2C_HandleTypeDef *hi2c1,uint16_t addr){
	uint8_t temp[2];
	HAL_StatusTypeDef ret=0;
	ret=HAL_I2C_Mem_Read(hi2c1,ADDR_TOSHIBA,addr,I2C_MEMADD_SIZE_16BIT,temp,2,HAL_MAX_DELAY);
	while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY){HAL_Delay(1);}
	return (temp[1]<<8)|temp[0];
}

uint32_t i2c1_uh2cd_read32(I2C_HandleTypeDef *hi2c1,uint16_t addr){
	uint8_t temp[4];
	HAL_StatusTypeDef ret=0;
	ret=HAL_I2C_Mem_Read(hi2c1,ADDR_TOSHIBA,addr,I2C_MEMADD_SIZE_16BIT,temp,4,HAL_MAX_DELAY);
	while(HAL_I2C_GetState(hi2c1)!=HAL_I2C_STATE_READY){HAL_Delay(1);}


	return (temp[3]<<24)|(temp[2]<<16)|(temp[1]<<8)|temp[0];
}

void data_send_COM_Info(UART_HandleTypeDef *huart, uint32_t data, uint16_t addr, uint8_t error){
  uint8_t temp_s[35];
  uint8_t temp[4];
  //data=0x21222324;
  temp[0]=data>>24 & 0xFF;
  temp[1]=data>>16 & 0xFF;
  temp[2]=data>>8 & 0xFF;
  temp[3]=data & 0xFF;
  snprintf(temp_s,35,"OK: %2d ADDR: %4x Read:%2x%2x%2x%2x\r\n",error,addr,temp[0],temp[1],temp[2],temp[3]);
  HAL_UART_Transmit(huart,temp_s,35,10);
  HAL_Delay(100);
};




