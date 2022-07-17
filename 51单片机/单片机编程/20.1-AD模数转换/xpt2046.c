#include<reg52.h>
sbit DIN=P3^4;
sbit CS=P3^5;
sbit DCLK=P3^6;
sbit DOUT=P3^7;
/*
brief:xpt2046芯片模数转换，不同指令读取不同输入的值转化为数字信号
    come_in:一个字节，控制读取的方式以及对象
    out:12位或八位二进制数
*/
unsigned int xpt2046_read(unsigned char type)
{
	unsigned char i;
	unsigned int out=0;
	DCLK=0;
	CS=0;
	for(i=0;i<8;i++)
	{
		DIN=(0x80>>i)&type;
		DCLK=1;
		DCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DCLK=1;
		DCLK=0;
		if(DOUT){out|=(0x8000>>i);}
	}   
	CS=1;
	if(type&0x08){out>>=8;}
	else{out>>=4;}
	return out;
}