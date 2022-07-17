#include<reg52.h>
sbit SDA=P2^0;
sbit SCL=P2^1;
unsigned char i;
void I2C_Start()//开始
{
	SDA=1;
	SCL=1;
	SDA=0;
	SCL=0;
}
void I2C_Stop()//结束
{
	SDA=0;
	SCL=1;
	SDA=1;
}
void I2C_WriteByte(unsigned char Byte)//写入一个字节
{
	for(i=0;i<8;i++)
	{
		SDA=Byte&(0x80>>i);
		SCL=1;
		SCL=0;
	}
}
unsigned char I2C_ReceiveByte()//接受字节
{
	unsigned char Byte=0x00;
	SDA=1;
	for(i=0;i<8;i++)
	{
		SCL=1;
		if(SDA){Byte|=(0x80>>i);}
		SCL=0;
	}
}
void I2C_SA(unsigned char Byte)//发送应答，1表非应答
{
	SDA=Byte;
	SCL=1;
	SCL=0;
}
unsigned char I2C_RA()//接受应答
{
	unsigned char y;
	SDA=1;
	SCL=1;
	y=SDA;
	SCL=0;
	return y;
}