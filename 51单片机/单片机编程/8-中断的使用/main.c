#include <reg51.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit LED=P2^0;
//sbit KEY=P3^2;
void delay(u16 i)
{
	while(i--);
}
void yuxian()
{
	EA=1;//中断总允许位
	EX0=1;//外部中断允许位
	IT0=1;//使触发方式为下降沿
}
void aihui () interrupt 0
{
	delay(1000);
	if(P3^2==0)
	{
		LED=~LED;
	}
}
void main()
{
	LED=0;
	yuxian();
	while(1);
	
}