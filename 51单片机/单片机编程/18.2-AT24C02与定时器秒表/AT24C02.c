#include<reg52.h>
#include"delay.h"
#include"I2C.h"
void AT24C02_Write(unsigned char Address,unsigned char Byte)
{
	I2C_Start();
	I2C_WriteByte(0xA0);
	I2C_RA();
	I2C_WriteByte(Address);
	I2C_RA();
	I2C_WriteByte(Byte);
	I2C_RA();
	I2C_Stop();
	delay(5);
}
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