#include<regx52.h>
#include"delay.h"
#include"UART.h"
/*
    brief:每一秒发送一个加一的值，可发送数据控制LED行
    come_in:void
    out:void
*/
void main()
{
	unsigned char a=0;
	UART_Init();
	while(1)
	{
		SendByte(a);
		a++;
		delay(1000);
	}
}
void RecieveByte() interrupt 4
{
	if(RI==1)
	{
		P2=SBUF;
		
		SendByte(SBUF);
		RI=0;
	}
}
