#ifndef __DS182B20_H__
#define __DS18B20_H__
void DS18B20_Init();
void DS18B20_WriteByte(unsigned char Byte);
unsigned char DS18B20_RecieveByte();
float DS18B20_ReadT(void);
void DS18B20_ConvertT(void);
#endif