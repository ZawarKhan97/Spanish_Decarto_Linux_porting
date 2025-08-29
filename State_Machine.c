#include "State_Machine_GIT.h"

void LCD_Init(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1){
    
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x8039);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0004);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x98FF); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0381);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x04BC);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0002);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x7303);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0004);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0005);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0A06);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0007);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0008);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0109);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x000A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x000B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x010C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x000D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x000E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1D0F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1D10);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0011);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0012);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0013);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0014);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0016);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0017);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0018);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0019);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x001A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x001B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x001C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x001D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x401E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x801F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0620);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0221);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0022);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0023);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0024);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0025);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0026);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0027);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x3328);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0329);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x002A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x002B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x002C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x002D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x002E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x002F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0030);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0031);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0032);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0033);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0434);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0035);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0036);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0037);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x3C38);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0039);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x403A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x403B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x003C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x003D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x003E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x003F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0040);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0041);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0042);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0043);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0044);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0150);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x2351);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4552);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x6753);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x8954);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xAB55);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0156);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x2357);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4558);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x6759);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x895A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xAB5B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xCD5C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xEF5D);

i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x115E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x015F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0060);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1561);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1462);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0E63);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0F64);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0C65);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0D66);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0667);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0268);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0769);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x026A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x026B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x026C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x026D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x026E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x026F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0270);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0271);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0272);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0273);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0274);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0175);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0076);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1477);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1578);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0E79);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0F7A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0C7B);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0D7C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x067D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x027E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x077F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0280);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0281);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0282);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0283);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0284);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0285);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0286);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0287);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0288);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0289);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x028A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x8039);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0004);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x98FF); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0481);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x156C);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x2B6E);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x336F);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x188D);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xBA87);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x7626);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xD1B2);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x06B5);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x243A);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1F35);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x8039);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0004);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x98FF); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0181);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0922);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0031);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x3340);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0xA253);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x9255);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x9650);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x9651);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x2260);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0061);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1962);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0063);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x08A0);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x11A1);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x19A2);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0DA3);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0DA4);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1EA5);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x14A6);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x17A7);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4FA8);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1AA9);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x27AA);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x49AB);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1AAC);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x18AD);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4CAE);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x22AF);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x27B0);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4BB1);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x60B2);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x39B3);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x08C0);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x11C1);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x19C2);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0DC3);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0DC4);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1EC5);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x14C6);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x17C7);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4FC8);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1AC9);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x27CA);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x49CB);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x1ACC);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x18CD);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4CCE);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x33CF);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x27D0);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x4BD1);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x60D2);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x39D3);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x8039);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0004);i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x98FF); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0081);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0005); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x11);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0035);
i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0015); i2c1_uh2cd_write16(huart,hi2c1,0x0504,0x0336);
}


void RS1(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
    // Initialization for Stand-by (RS1)
    // Software Reset
    i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0004); // ConfCtl0
    i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x3F00); // SysCtl
    i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x0000); // SysCtl
	i2c1_uh2cd_write16(huart,hi2c1,0x0006,0x0008); // ConfCtl1   	i2c1_uh2cd_write16(huart,hi2c1,0x0006, 0x0008);
    // HDMI Interrupt Mask, Clear
    i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0F3F); // IntMask
    i2c1_uh2cd_write8(huart,hi2c1,0x8502, 0xFF); // SYS_INT
    i2c1_uh2cd_write8(huart,hi2c1,0x850B, 0xFF); // MISC_INT
    i2c1_uh2cd_write16(huart,hi2c1,0x0014, 0x0F3F); // IntStatus
    i2c1_uh2cd_write8(huart,hi2c1,0x8512, 0xFE); // SYS_INTM
    i2c1_uh2cd_write8(huart,hi2c1,0x851B, 0xFD); // MISC_INTM
    // HDMI PHY
    i2c1_uh2cd_write8(huart,hi2c1,0x8410, 0x03); // PHY CTL
    i2c1_uh2cd_write8(huart,hi2c1,0x8413, 0x3F); // PHY_ENB
    i2c1_uh2cd_write8(huart,hi2c1,0x8420, 0x07); // EQ_BYPS
    i2c1_uh2cd_write8(huart,hi2c1,0x84F0, 0x31); // APLL_CTL
    i2c1_uh2cd_write8(huart,hi2c1,0x84F4, 0x01); // DDCIO_CTL
    // HDMI Clock
    i2c1_uh2cd_write16(huart,hi2c1,0x8540, 0x12C0); // SYS_FREQ0_1
    i2c1_uh2cd_write8(huart,hi2c1,0x8630, 0x00); // LOCKDET_FREQ0
    i2c1_uh2cd_write16(huart,hi2c1,0x8631, 0x0753); // LOCKDET_REF1_2
    i2c1_uh2cd_write8(huart,hi2c1,0x8670, 0x02); // NCO_F0_MOD
    i2c1_uh2cd_write16(huart,hi2c1,0x8A0C, 0x12C0); // CSC_SCLK0_1
    // EDID
    i2c1_uh2cd_write8(huart,hi2c1,0x85E0, 0x01); // EDID_MODE
    i2c1_uh2cd_write16(huart,hi2c1,0x85E3, 0x0100); // EDID_LEN1_2
    // EDID Data
    i2c1_uh2cd_write8(huart,hi2c1,0x8C00, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C01, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C02, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C03, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C04, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C05, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C06, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C07, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C08, 0x52); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C09, 0x62); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C0A, 0x88); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C0B, 0x88); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C0C, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C0D, 0x88); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C0E, 0x88); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C0F, 0x88); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C10, 0x2D); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C11, 0x1E); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C12, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C13, 0x03); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C14, 0x80); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C15, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C16, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C17, 0x78); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C18, 0x0A); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C19, 0x0D); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C1A, 0xC9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C1B, 0xA0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C1C, 0x57); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C1D, 0x47); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C1E, 0x98); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C1F, 0x27); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C20, 0x12); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C21, 0x48); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C22, 0x4C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C23, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C24, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C25, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C26, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C27, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C28, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C29, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C2A, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C2B, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C2C, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C2D, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C2E, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C2F, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C30, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C31, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C32, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C33, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C34, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C35, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C36, 0xD9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C37, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C38, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C39, 0x76); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C3A, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C3B, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C3C, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C3D, 0x50); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C3E, 0x2C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C3F, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C40, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C41, 0x04); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C42, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C43, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C44, 0x25); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C45, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C46, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C47, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C48, 0xD9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C49, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C4A, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C4B, 0x76); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C4C, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C4D, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C4E, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C4F, 0x50); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C50, 0x2C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C51, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C52, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C53, 0x04); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C54, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C55, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C56, 0x25); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C57, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C58, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C59, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C5A, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C5B, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C5C, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C5D, 0xFC); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C5E, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C5F, 0x54); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C60, 0x6F); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C61, 0x73); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C62, 0x68); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C63, 0x69); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C64, 0x62); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C65, 0x61); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C66, 0x2D); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C67, 0x55); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C68, 0x48); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C69, 0x32); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C6A, 0x44); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C6B, 0x0A); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C6C, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C6D, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C6E, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C6F, 0xFD); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C70, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C71, 0x14); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C72, 0x78); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C73, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C74, 0xFF); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C75, 0x1D); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C76, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C77, 0x0A); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C78, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C79, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C7A, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C7B, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C7C, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C7D, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C7E, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C7F, 0x03); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C80, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C81, 0x03); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C82, 0x1A); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C83, 0xF2); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C84, 0x47); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C85, 0xC6); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C86, 0xC6); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C87, 0x46); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C88, 0x46); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C89, 0x46); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C8A, 0x46); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C8B, 0x46); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C8C, 0x23); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C8D, 0x09); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C8E, 0x07); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C8F, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C90, 0x83); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C91, 0x01); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C92, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C93, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C94, 0x65); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C95, 0x03); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C96, 0x0C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C97, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C98, 0x10); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C99, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C9A, 0xD9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C9B, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C9C, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C9D, 0x76); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C9E, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8C9F, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA0, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA1, 0x50); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA2, 0x2C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA3, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA4, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA5, 0x04); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA6, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA7, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA8, 0x25); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CA9, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CAA, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CAB, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CAC, 0xD9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CAD, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CAE, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CAF, 0x76); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB0, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB1, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB2, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB3, 0x50); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB4, 0x2C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB5, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB6, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB7, 0x04); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB8, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CB9, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CBA, 0x25); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CBB, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CBC, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CBD, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CBE, 0xD9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CBF, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC0, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC1, 0x76); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC2, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC3, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC4, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC5, 0x50); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC6, 0x2C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC7, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC8, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CC9, 0x04); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CCA, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CCB, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CCC, 0x25); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CCD, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CCE, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CCF, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD0, 0xD9); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD1, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD2, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD3, 0x76); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD4, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD5, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD6, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD7, 0x50); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD8, 0x2C); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CD9, 0x20); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CDA, 0x02); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CDB, 0x04); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CDC, 0xD0); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CDD, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CDE, 0x25); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CDF, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE0, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE1, 0x18); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE2, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE3, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE4, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE5, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE6, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE7, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE8, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CE9, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CEA, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CEB, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CEC, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CED, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CEE, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CEF, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF0, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF1, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF2, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF3, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF4, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF5, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF6, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF7, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF8, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CF9, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CFA, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CFB, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CFC, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CFD, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CFE, 0x00); // EDID_RAM
    i2c1_uh2cd_write8(huart,hi2c1,0x8CFF, 0xEA); // EDID_RAM
    // HDCP Setting
    // HDMI SYSTEM
    i2c1_uh2cd_write8(huart,hi2c1,0x8543, 0x02); // DDC_CTL
    i2c1_uh2cd_write8(huart,hi2c1,0x8544, 0x10); // HPD_CTL
    // HDMI Audio Setting
    i2c1_uh2cd_write8(huart,hi2c1,0x8600, 0x00); // AUD_Auto_Mute
    i2c1_uh2cd_write8(huart,hi2c1,0x8602, 0xF3); // Auto_CMD0
    i2c1_uh2cd_write8(huart,hi2c1,0x8603, 0x02); // Auto_CMD1
    i2c1_uh2cd_write8(huart,hi2c1,0x8604, 0x0C); // Auto_CMD2
    i2c1_uh2cd_write8(huart,hi2c1,0x8606, 0x05); // BUFINIT_START
    i2c1_uh2cd_write8(huart,hi2c1,0x8607, 0x00); // FS_MUTE
    i2c1_uh2cd_write8(huart,hi2c1,0x8652, 0x02); // SDO_MODE1


/*
    // Check HDMI cable status
    i2c1_uh2cd_read8(hi2c1,0x8520); //Check if bit0=1 (DDC_5V is ON)
    i2c1_uh2cd_read8(hi2c1,0x8520); //
    i2c1_uh2cd_read8(hi2c1,0x8520); //

*/

    if ((i2c1_uh2cd_read8(hi2c1,0x8520)) & 0x01) //Active HPDOut in TC358870
    {
        RS2(huart,hi2c1);
    }


    // Enable Interrupt
    i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0F1F); // IntMask
    // Enter Sleep
    i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x0001); // SysCtl

}

void RS2(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
	// Initialization for Ready (RS2)
	// Enable Interrupt
	i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0D3F); // IntMask
	// Set HPDO to "H"
	i2c1_uh2cd_write8(huart,hi2c1,0x854A, 0x01); // INIT_END
}

void RS3(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
    // MIPI Output Enable(RS3)
    // Check HDMI resolution/format
    //HAL_Delay(1000);
    // MIPI Output Setting
    // Stop Video and Audio
    i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C32); // ConfCtl0
    // Soft Reset CSI-TX and Splitter Block
    i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x1200); // SysCtl
    i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x0000); // SysCtl
    // Video Color Format Setting
    i2c1_uh2cd_write8(huart,hi2c1,0x8A02, 0x42); // VOUT_SYNC0
    // DSI-TX0 Transition Timing
   i2c1_uh2cd_write32(huart,hi2c1,0x0108, 0x00000001); // DSI_TX_CLKEN
   i2c1_uh2cd_write32(huart,hi2c1,0x010C, 0x00000001); // DSI_TX_CLKSEL
   i2c1_uh2cd_write32(huart,hi2c1,0x02A0, 0x00000001); // MIPI_PLL_CONTROL
   i2c1_uh2cd_write32(huart,hi2c1,0x02AC, 0x000094C7); // MIPI_PLL_CNF
    HAL_Delay(1);
   i2c1_uh2cd_write32(huart,hi2c1,0x02A0, 0x00000003); // MIPI_PLL_CONTROL
   i2c1_uh2cd_write32(huart,hi2c1,0x0118, 0x00000014); // LANE_ENABLE
   i2c1_uh2cd_write32(huart,hi2c1,0x0120, 0x00001770); // LINE_INIT_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0124, 0x00000000); // HSTX_TO_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0128, 0x00000101); // FUNC_ENABLE
   i2c1_uh2cd_write32(huart,hi2c1,0x012C, 0x00000000); // DSI_LPTX_MODE
   i2c1_uh2cd_write32(huart,hi2c1,0x0130, 0x00010000); // DSI_TATO_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0134, 0x00005000); // DSI_PRESP_BTA_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0138, 0x00010000); // DSI_PRESP_LPR_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x013C, 0x00010000); // DSI_PRESP_LPW_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0140, 0x00010000); // DSI_PRESP_HSR_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0144, 0x00010000); // DSI_PRESP_HSW_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0148, 0x00001000); // DSI_PR_TO_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x014C, 0x00010000); // DSI_LRX-H_TO_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0150, 0x00000160); // FUNC_MODE
   i2c1_uh2cd_write32(huart,hi2c1,0x0154, 0x00000001); // DSI_RX_VC_ENABLE
   i2c1_uh2cd_write32(huart,hi2c1,0x0158, 0x000000C8); // IND_TO_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0164, 0x00000014); // INIT_INT_MSK
   i2c1_uh2cd_write32(huart,hi2c1,0x0168, 0x0000002A); // DSI_HSYNC_STOP_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0170, 0x00000302); // APF_VDELAYCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0178, 0x00000001); // APF_VC_CONFIG
   i2c1_uh2cd_write32(huart,hi2c1,0x017C, 0x00000081); // DSI_TX_MODE
   i2c1_uh2cd_write32(huart,hi2c1,0x018C, 0x00000079); // DSI_HSYNC_WIDTH
   i2c1_uh2cd_write32(huart,hi2c1,0x0190, 0x00000118); // DSI_HBPR
   i2c1_uh2cd_write32(huart,hi2c1,0x01A4, 0x00000000); // DSI_RX_STATE_INT_MASK
   i2c1_uh2cd_write32(huart,hi2c1,0x01AC, 0x00000000); // DSI_RXTRG_INT_MASK
   i2c1_uh2cd_write32(huart,hi2c1,0x01C0, 0x00000015); // DSI_LPRX_THRESH_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x020C, 0x00000000); // DSI_PRTO_INT_MASK
   i2c1_uh2cd_write32(huart,hi2c1,0x0214, 0x00000000); // APP_SIDE_ERR_INT_MASK
   i2c1_uh2cd_write32(huart,hi2c1,0x021C, 0x00000080); // DSI_RX_ERR_INT_MASK
   i2c1_uh2cd_write32(huart,hi2c1,0x0224, 0x00000000); // DSI_LPTX_INT_MASK
   i2c1_uh2cd_write32(huart,hi2c1,0x0240, 0x00000000); // DPHY_DLYCNTRL
   i2c1_uh2cd_write32(huart,hi2c1,0x0254, 0x00000004); // LPTXTIMECNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0258, 0x001E0003); // TCLK_HEADERCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x025C, 0x000A0004); // TCLK_TRAILCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0260, 0x000A0003); // THS_HEADERCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0264, 0x00004E20); // TWAKEUPCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0268, 0x0000000C); // TCLK_POSTCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x026C, 0x000A0004); // THS_TRAILCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0270, 0x00000020); // HSTXVREGCNT
   i2c1_uh2cd_write32(huart,hi2c1,0x0274, 0x0000001F); // HSTXVREGEN
   i2c1_uh2cd_write32(huart,hi2c1,0x0278, 0x00040006); // BTA_COUNT
   i2c1_uh2cd_write32(huart,hi2c1,0x027C, 0x00000002); // DPHY_TX ADJUST
   i2c1_uh2cd_write32(huart,hi2c1,0x0288, 0x000002AA); // DPHY_CAP
   i2c1_uh2cd_write32(huart,hi2c1,0x011C, 0x00000001); // DSITX_START
    // DSI-TX1 Transition Timing
    // Command Transmission Before Video Start
    i2c1_uh2cd_write16(huart,hi2c1,0x0500, 0x0000); // CMD_SEL
    i2c1_uh2cd_write32(huart,hi2c1,0x0110, 0x00000016); // MODE_CONFIG
    i2c1_uh2cd_write32(huart,hi2c1,0x0310, 0x00000016); // MODE_CONFIG

    LCD_Init(huart,hi2c1);

    // Exit Sleep
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0011); // DCSCMD_Q
    HAL_Delay(150);
    // MCAP
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0023); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x00B0); // DCSCMD_Q
    HAL_Delay(1);
    // Backlight Control 4 //Si no se pone, vibra
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x8029); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0014); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x7DCE); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x4840); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x6756); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x8878); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0xA798); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0xC3B5); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0xDED1); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0xF2E9); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0xFFFA); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0004); // DCSCMD_Q
    // Split Control
    i2c1_uh2cd_write16(huart,hi2c1,0x5000, 0x0000); // STX0_CTL
    i2c1_uh2cd_write16(huart,hi2c1,0x500C, 0x0000); // STX0_FPX
    i2c1_uh2cd_write16(huart,hi2c1,0x500E, 0x02CF); // STX0_LPX
    i2c1_uh2cd_write16(huart,hi2c1,0x5080, 0x0000); // STX1_CTL
    i2c1_uh2cd_write16(huart,hi2c1,0x508C, 0x0000); // STX1_FPX
    i2c1_uh2cd_write16(huart,hi2c1,0x508E, 0x02CF); // STX1_LPX
    i2c1_uh2cd_write16(huart,hi2c1,0x7080, 0x0080); // STX_DBG
    i2c1_uh2cd_write16(huart,hi2c1,0x5008, 0x0870); // STX0_WC
    i2c1_uh2cd_write16(huart,hi2c1,0x5088, 0x0870); // STX1_WC
    // Enable Interrupt
    i2c1_uh2cd_write8(huart,hi2c1,0x8502, 0xFF); // SYS_INT
    i2c1_uh2cd_write8(huart,hi2c1,0x8503, 0xFF); // CLK_INT
    i2c1_uh2cd_write8(huart,hi2c1,0x8504, 0xFF); // PACKET_INT
    i2c1_uh2cd_write8(huart,hi2c1,0x8505, 0xFF); // CBIT_INT
    i2c1_uh2cd_write8(huart,hi2c1,0x8506, 0xFF); // AUDIO_INT
    i2c1_uh2cd_write8(huart,hi2c1,0x850B, 0xFF); // MISC_INT
    i2c1_uh2cd_write16(huart,hi2c1,0x0014, 0x0F3F); // IntStatus
    i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0D3F); // IntMask
    // Start Video TX
    i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C35); // ConfCtl0
    i2c1_uh2cd_write16(huart,hi2c1,0x0006, 0x0000); // ConfCtl1
    // Command Transmission After Video Start.
   i2c1_uh2cd_write32(huart,hi2c1,0x0110, 0x00000006); // MODE_CONFIG
   i2c1_uh2cd_write32(huart,hi2c1,0x0310, 0x00000006); // MODE_CONFIG
	HAL_Delay(10);
    // MCAP
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0023); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x00B0); // DCSCMD_Q
	HAL_Delay(10);
    // Interface Setting
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0023); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x14B3); // DCSCMD_Q
	HAL_Delay(10);
    // MCAP
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0023); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x03B0); // DCSCMD_Q
	HAL_Delay(10);
    // Set Display On
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
    i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0029); // DCSCMD_Q
    HAL_Delay(32);
}

void RS4(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
	// MIPI Output Disable(RS4)
	// Reset Display by H/W reset
	// Stop DSI output
	// Set Display OFF
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0028); // DCSCMD_Q
	HAL_Delay(100);

	i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C34); // ConfCtl0
	// Enable Interrupt
	i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0D3F); // IntMask

}

void RS5(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
	// MIPI Output Disable & Sleep(RS5)
	// Reset Display by H/W reset
	// Stop DSI output
	// Set Display OFF
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0028); // DCSCMD_Q
	HAL_Delay(100);
	// In Sleep
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0010); // DCSCMD_Q
	HAL_Delay(200);

	i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C34); // ConfCtl0
	// Enable Interrupt
	i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0F1F); // IntMask
	// Enter Sleep
	i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x0001); // SysCtl   1: Sleep mode/0: Normal operation

}

void RS_DO(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
	// Auto Disp Off(RS_DO)
	// Software Reset
	i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C34); // ConfCtl0
	i2c1_uh2cd_write16(huart,hi2c1,0x0006, 0x0008); // ConfCtl1
	i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x1200); // SysCtl
	i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x0000); // SysCtl
	i2c1_uh2cd_write16(huart,hi2c1,0x0006, 0x0000); // ConfCtl1
	i2c1_uh2cd_write16(huart,hi2c1,0x7000, 0x0009); // CB_CTL
	// DSI-TX1 Transition Timing
	i2c1_uh2cd_write32(huart,hi2c1,0x0308, 0x00000001); // DSI_TX_CLKEN
	i2c1_uh2cd_write32(huart,hi2c1,0x030C, 0x00000001); // DSI_TX_CLKSEL
	i2c1_uh2cd_write32(huart,hi2c1,0x04A0, 0x00000001); // MIPI_PLL_CONTROL
	i2c1_uh2cd_write32(huart,hi2c1,0x04AC, 0x000094C7); // MIPI_PLL_CNF
	HAL_Delay(1);
	i2c1_uh2cd_write32(huart,hi2c1,0x04A0, 0x00000003); // MIPI_PLL_CONTROL
	i2c1_uh2cd_write32(huart,hi2c1,0x0318, 0x00000014); // LANE_ENABLE
	i2c1_uh2cd_write32(huart,hi2c1,0x0320, 0x00001770); // LINE_INIT_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0324, 0x00000000); // HSTX_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0328, 0x00000101); // FUNC_ENABLE
	i2c1_uh2cd_write32(huart,hi2c1,0x0330, 0x00010000); // DSI_TATO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0334, 0x00005000); // DSI_PRESP_BTA_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0338, 0x00010000); // DSI_PRESP_LPR_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x033C, 0x00010000); // DSI_PRESP_LPW_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0340, 0x00010000); // DSI_PRESP_HSR_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0344, 0x00010000); // DSI_PRESP_HSW_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0348, 0x00001000); // DSI_PR_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x034C, 0x00010000); // DSI_LRX-H_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0350, 0x00000161); // FUNC_MODE
	i2c1_uh2cd_write32(huart,hi2c1,0x0354, 0x00000001); // DSI_RX_VC_ENABLE
	i2c1_uh2cd_write32(huart,hi2c1,0x0358, 0x000000C8); // IND_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0368, 0x0000002A); // DSI_HSYNC_STOP_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0370, 0x00000300); // APF_VDELAYCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x037C, 0x00000081); // DSI_TX_MODE
	i2c1_uh2cd_write32(huart,hi2c1,0x038C, 0x00000001); // DSI_HSYNC_WIDTH
	i2c1_uh2cd_write32(huart,hi2c1,0x0390, 0x00000104); // DSI_HBPR
	i2c1_uh2cd_write32(huart,hi2c1,0x03A4, 0x00000000); // DSI_RX_STATE_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x03C0, 0x00000015); // DSI_LPRX_THRESH_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0414, 0x00000000); // APP_SIDE_ERR_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x041C, 0x00000080); // DSI_RX_ERR_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x0424, 0x00000000); // DSI_LPTX_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x0454, 0x00000004); // LPTXTIMECNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0458, 0x001E0003); // TCLK_HEADERCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x045C, 0x000A0006); // TCLK_TRAILCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0460, 0x000A0003); // THS_HEADERCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0464, 0x00003E80); // TWAKEUPCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0468, 0x0000000C); // TCLK_POSTCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x046C, 0x000A0004); // THS_TRAILCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0470, 0x00000020); // HSTXVREGCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0474, 0x0000001F); // HSTXVREGEN
	i2c1_uh2cd_write32(huart,hi2c1,0x0478, 0x00040005); // BTA_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x047C, 0x00000002); // DPHY_TX ADJUST
	i2c1_uh2cd_write32(huart,hi2c1,0x031C, 0x00000001); // DSITX_START
	// DSI-TX0 Transition Timing
	i2c1_uh2cd_write32(huart,hi2c1,0x0108, 0x00000001); // DSI_TX_CLKEN
	i2c1_uh2cd_write32(huart,hi2c1,0x010C, 0x00000001); // DSI_TX_CLKSEL
	i2c1_uh2cd_write32(huart,hi2c1,0x02A0, 0x00000001); // MIPI_PLL_CONTROL
	i2c1_uh2cd_write32(huart,hi2c1,0x02AC, 0x000094C7); // MIPI_PLL_CNF
	HAL_Delay(1);
	i2c1_uh2cd_write32(huart,hi2c1,0x02A0, 0x00000003); // MIPI_PLL_CONTROL
	i2c1_uh2cd_write32(huart,hi2c1,0x0118, 0x00000014); // LANE_ENABLE
	i2c1_uh2cd_write32(huart,hi2c1,0x0120, 0x00001770); // LINE_INIT_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0124, 0x00000000); // HSTX_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0128, 0x00000101); // FUNC_ENABLE
	i2c1_uh2cd_write32(huart,hi2c1,0x0130, 0x00010000); // DSI_TATO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0134, 0x00005000); // DSI_PRESP_BTA_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0138, 0x00010000); // DSI_PRESP_LPR_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x013C, 0x00010000); // DSI_PRESP_LPW_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0140, 0x00010000); // DSI_PRESP_HSR_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0144, 0x00010000); // DSI_PRESP_HSW_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0148, 0x00001000); // DSI_PR_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x014C, 0x00010000); // DSI_LRX-H_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0150, 0x00000161); // FUNC_MODE
	i2c1_uh2cd_write32(huart,hi2c1,0x0154, 0x00000001); // DSI_RX_VC_ENABLE
	i2c1_uh2cd_write32(huart,hi2c1,0x0158, 0x000000C8); // IND_TO_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0168, 0x0000002A); // DSI_HSYNC_STOP_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0170, 0x00000300); // APF_VDELAYCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x017C, 0x00000081); // DSI_TX_MODE
	i2c1_uh2cd_write32(huart,hi2c1,0x018C, 0x00000079); // DSI_HSYNC_WIDTH
	i2c1_uh2cd_write32(huart,hi2c1,0x0190, 0x00000118); // DSI_HBPR
	i2c1_uh2cd_write32(huart,hi2c1,0x01A4, 0x00000000); // DSI_RX_STATE_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x01C0, 0x00000015); // DSI_LPRX_THRESH_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0214, 0x00000000); // APP_SIDE_ERR_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x021C, 0x00000080); // DSI_RX_ERR_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x0224, 0x00000000); // DSI_LPTX_INT_MASK
	i2c1_uh2cd_write32(huart,hi2c1,0x0254, 0x00000004); // LPTXTIMECNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0258, 0x001E0003); // TCLK_HEADERCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x025C, 0x000A0006); // TCLK_TRAILCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0260, 0x000A0003); // THS_HEADERCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0264, 0x00003E80); // TWAKEUPCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0268, 0x0000000C); // TCLK_POSTCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x026C, 0x000A0004); // THS_TRAILCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0270, 0x00000020); // HSTXVREGCNT
	i2c1_uh2cd_write32(huart,hi2c1,0x0274, 0x0000001F); // HSTXVREGEN
	i2c1_uh2cd_write32(huart,hi2c1,0x0278, 0x00040005); // BTA_COUNT
	i2c1_uh2cd_write32(huart,hi2c1,0x027C, 0x00000002); // DPHY_TX ADJUST
	i2c1_uh2cd_write32(huart,hi2c1,0x011C, 0x00000001); // DSITX_START
	// Command Transmission Before Video Start
	i2c1_uh2cd_write16(huart,hi2c1,0x0500, 0x0004); // CMD_SEL
	// Split Control
	i2c1_uh2cd_write16(huart,hi2c1,0x5000, 0x0100); // STX0_CTL
	i2c1_uh2cd_write16(huart,hi2c1,0x500C, 0x0000); // STX0_FPX
	i2c1_uh2cd_write16(huart,hi2c1,0x500E, 0x02CF); // STX0_LPX
	i2c1_uh2cd_write16(huart,hi2c1,0x5080, 0x0100); // STX1_CTL
	i2c1_uh2cd_write16(huart,hi2c1,0x508C, 0x0000); // STX1_FPX
	i2c1_uh2cd_write16(huart,hi2c1,0x508E, 0x02CF); // STX1_LPX
	// Color Bar Setting
	i2c1_uh2cd_write16(huart,hi2c1,0x7008, 0x0020); // CB_HSW
	i2c1_uh2cd_write16(huart,hi2c1,0x700A, 0x0002); // CB_VSW
	i2c1_uh2cd_write16(huart,hi2c1,0x700C, 0x0346); // CB_Htotal
	i2c1_uh2cd_write16(huart,hi2c1,0x700E, 0x0520); // CB_Vtotal
	i2c1_uh2cd_write16(huart,hi2c1,0x7010, 0x02D0); // CB_Hact
	i2c1_uh2cd_write16(huart,hi2c1,0x7012, 0x0500); // CB_Vact
	i2c1_uh2cd_write16(huart,hi2c1,0x7014, 0x004A); // CB_Hstart
	i2c1_uh2cd_write16(huart,hi2c1,0x7016, 0x0010); // CB_Vstart
	i2c1_uh2cd_write16(huart,hi2c1,0x7000, 0x000D); // CB_CTL
	// Start Video TX
	i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C37); // ConfCtl0
	// Command Transmission After Video Start. HS command TX
	i2c1_uh2cd_write32(huart,hi2c1,0x0110, 0x00000006); // MODE_CONFIG
	i2c1_uh2cd_write32(huart,hi2c1,0x0310, 0x00000006); // MODE_CONFIG
	// Set Display Off
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0028); // DCSCMD_Q
	HAL_Delay(100);
	// Enter Sleep
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0005); // DCSCMD_Q
	i2c1_uh2cd_write16(huart,hi2c1,0x0504, 0x0010); // DCSCMD_Q
	HAL_Delay(200);
	i2c1_uh2cd_write16(huart,hi2c1,0x0004, 0x0C34); // ConfCtl0
	i2c1_uh2cd_write16(huart,hi2c1,0x7000, 0x0000); // CB_CTL
}


/*
0x001A<0>=1 => Change state from S1-> S2. Execute ""Inialization for Ready(RS2)
0x850B<1>=1 & 0x8520<7>=1  => Change state from S2->S3.  Execute ""MIPI Output Enable(RS3)
0x8502<0>=1 & 0x8520<0>=0  => Change state from S3-> S1. Execute ""MIPI output disable & Sleep(RS5)
0x850B<1>=1 & 0x8520<0>=1 & 0x8520<7>=0 => Change state from S3-> S2. Execute ""MIPI output disable(RS4)
*/

void int_status_check(UART_HandleTypeDef *huart,I2C_HandleTypeDef *hi2c1)
{
	uint16_t status = 0, int_sys_status = 0;
	uint8_t sys_int = 0, sys_status = 0;
	uint8_t hdmi_int = 0;

	i2c1_uh2cd_write16(huart,hi2c1,0x0002, 0x0000); // SysCtl
	HAL_Delay(10);

	//Check Interrupt
	//Check if bit5=1 (SYS Interrupt in sleep mode), bit9=1 (HDMI-RX interrupt)

	status = i2c1_uh2cd_read16(hi2c1,0x0014);
	data_send_COM_Info(huart,status,0x0014, 0x00);
	//int_sys_status = i2c1_uh2cd_read16(hi2c1,0x001A);
	//data_send_COM_Info(huart,status,0x001A, 0x00);

	//Check bit5 (SYS_INT interrupt).
	if (status & 0x2000) { //Interrupt de HDMI-RX
		int_sys_status = i2c1_uh2cd_read16(hi2c1,0x001A);
		data_send_COM_Info(huart,status,0x001A, 0x00);
		//Check 0x001A<0>=1 (HPDI Change interrupt)
		/*if (int_sys_status & 0x0100) {
			RS2(huart,hi2c1);
			HAL_UART_Transmit(huart,"RS2\r\n",6,10);
			//printf("RS2\r\n");
		}*/
	}

	//Check bit9 (HDMI-RX interrupt).
	if (status & 0x0200) {
		//Check 0x850B<1>=1 & 0x8520<7>=1
		hdmi_int = i2c1_uh2cd_read8(hi2c1,0x850B);
		//Check if bit1=1 (Sync Change interrupt)
		if (hdmi_int & 0x02) {
			sys_status = i2c1_uh2cd_read8(hi2c1,0x8520); // SYS_STATUS
			data_send_COM_Info(huart,status ,0x8520, 0x00);
			if (sys_status & 0x80) {
				//Jdi_DC_En();
				//HAL_Delay(5);
				//Jdi_Rst_high();
				//HAL_Delay(10);
				//Jdi_Rst();
				//HAL_Delay(10);
				//Jdi_Rst_high();
				HAL_Delay(10);
				RS3(huart,hi2c1);
				HAL_UART_Transmit(huart,"RS3\r\n",6,10);
				HAL_Delay(200);
				
			}
			//Check 0x850B<1>=1 & 0x8520<0>=1 & 0x8520<7>=0
			if (sys_status & 0x01) {
				if (!(sys_status & 0x80)) {
					//Jdi_LED_Close();
					//Audio_off();
					RS4(huart,hi2c1);
					HAL_UART_Transmit(huart,"RS4\r\n",6,10);
					//Jdi_DC_Close();
					//Jdi_Rst();
					//HAL_Delay(100);
					//DebugLED_En();
					HAL_Delay(250);
					//DebugLED_close();
					HAL_Delay(250);
					//printf("RS4\r\n");
				}
			}
		}
	}
	//Check 0x8502<0>=1 & 0x8520<0>=0
	sys_int = i2c1_uh2cd_read8(hi2c1,0x8502); // SYS_INT. Check bit0 (DDC interrupt).
	//data_send_COM_Info(huart,sys_int,0x8502, 0x00);
	//sys_status = i2c1_uh2cd_read8(hi2c1,0x8520); // SYS_STATUS. Check bit0 (Status of 5V).
	//data_send_COM_Info(huart,sys_status,0x8520, 0x00);
	if (sys_int & 0x01) {
		sys_status = i2c1_uh2cd_read8(hi2c1,0x8520); // SYS_STATUS. Check bit0 (Status of 5V).
		data_send_COM_Info(huart,sys_status,0x8520, 0x00);
		if (!(sys_status & 0x01)) {
			//Jdi_LED_Close();
			//Jdi_DC_Close();
			//Jdi_Rst();
			//Audio_off();
			HAL_Delay(10);
			RS5(huart,hi2c1);
			HAL_UART_Transmit(huart,"RS5\r\n",6,10);
			//printf("RS5\r\n");
		} else if(sys_status & 0x01) {
			RS2(huart,hi2c1);
			//printf("RS1-RS2\r\n");
		}
	}

	/*i2c1_uh2cd_write16(huart,hi2c1,0x0016, 0x0F3F); // IntMask
	i2c1_uh2cd_write8(huart,hi2c1,0x8502, 0x00);    // SYS_INT
	i2c1_uh2cd_write8(huart,hi2c1,0x850B, 0x00);    // MISC_INT
	i2c1_uh2cd_write16(huart,hi2c1,0x0014, 0x0F3F); // IntStatus
*/
}

