#include<reg52.h>
sbit IC=P3^7;
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE
/*
    brief:初始化
    come_in:
    out:
*/
void DS18B20_Init()
{
	unsigned char i;
	IC=1;
	IC=0;
	i = 221;while (--i);//480us
	IC=1;
	i = 22;while (--i);//50us
	i = 221;while (--i);//480us
}
/*
    brief:写入一位
    come_in:写入的逻辑值
    out:
*/
void DS18B20_Write(unsigned char a)
{
	unsigned char i;
	IC=0;
	i = 4;while (--i);//11us
	if(a){IC=1;while (--i);}//56us
	else{i = 25;while (--i);IC=1;}//56us
}
/*
    brief:接收一位
    come_in:
    out:一位逻辑值
*/
unsigned char DS1802_Receive()
{
	unsigned char i,j;
	IC=0;
	i = 2;while (--i);//6us
	IC=1;
	i = 2;while (--i);//6us
	if(IC){j= 1;}
	else {j=0;}
	i = 22;while (--i);//50us
	return j;
}
/*
    brief:写入一个字节
    come_in:要写入的字节
    out:
*/
void DS18B20_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{DS18B20_Write(Byte&(0x01<<i));}
}
/*
    brief:接受一个字节
    come_in:
    out:一个字节
*/
unsigned char DS18B20_ReceiveByte()
{
	unsigned char i,Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(DS1802_Receive()){Byte|=(0x01<<i);}
	}
	return Byte;
}

	

