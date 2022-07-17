#include<reg52.h>
#include"Timer0.h"
#include"logic.h"
sbit IN1=P2^0;
sbit IN2=P2^1;
sbit IN3=P2^2;
sbit IN4=P2^3; 
sbit CTRL=P0^1;
sbit OUT1=P0^2;
sbit OUT2=P0^3;
sbit OUT3=P0^4;
sbit OUT4=P0^5;
sbit CTRR=P0^6;
int left=0,right=0;
void main()
{
	OUT1=1;
	OUT2=0;
	OUT3=0;
	OUT4=1;
	Timer0Init();
	while(1)
	{
		logic(IN1,IN2,IN3,IN4);
	}
}
void Timer0(void)		interrupt 1
{
	static unsigned int count;
	TL0 = 0xA4;		
	TH0 = 0xFF;		
	count++;
	if(count<left){	CTRL=1;}
	else					{ CTRL=0;}
	if(count<right){CTRR=1;}
	else           {CTRR=0;}
	count%=100;
}
