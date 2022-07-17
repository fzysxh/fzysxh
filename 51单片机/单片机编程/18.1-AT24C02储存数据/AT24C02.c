#include<reg52.h>
#include"delay.h"
#include"I2C.h"
/*
    brief:向指定地址写入字节
    come_in:要写入的地址，要写入的内容
    out:
*/
void AT24C02_Write(unsigned char Address,unsigned char Byte)
{
	I2C_Start();
	I2C_WriteByte(0xA0);//本单片机上ADT24C02对应位为0xA0
	I2C_RA();
	I2C_WriteByte(Address);
	I2C_RA();
	I2C_WriteByte(Byte);
	I2C_RA();
	I2C_Stop();
	delay(5);
}
/*
    brief:读取指定位的内容
    come_in:要读取的地址
    out:指定地址的内容
*/
unsigned char	AT24C02_Receive(unsigned char Address)
{
	unsigned char Byte;
	I2C_Start();
	I2C_WriteByte(0xA0);
	I2C_RA();
	I2C_WriteByte(Address);
	I2C_RA();
	I2C_Start();
	I2C_WriteByte(0xA1);
	I2C_RA();
	Byte=I2C_ReceiveByte();
	I2C_SA(1);
	I2C_Stop();
	return Byte;
}