/*
    brief：输出输入的值
    come_in:
    out:
*/
#include<regx52.h>
sbit SER=P3^4;
sbit RCK=P3^5;
sbit SRCK=P3^6;

void _74HC595(unsigned char Byte)
{
	unsigned char i;
	RCK=0;
	SRCK=0;
	for(i=0;i<8;i++)
	{
		
		SER=Byte&(0x80>>i);
		SRCK=1;
		SRCK=0;
	}
	RCK=1;
	RCK=0;
}
