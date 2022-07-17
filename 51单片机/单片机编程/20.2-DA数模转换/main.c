#include<reg52.h>
#include"Timer0.h"
#include"delay.h"
unsigned char high=0,i;
sbit DA=P2^1;
void main()
{

	Timer0Init();
	while(1)
	{
		for(i=0;i<100;i++)
		{
			high=i;
			delay(10);
		}
		for(i=100;i>0;i--)
		{
			high=i;
		delay(10);
		}
	}
}
void Timer0(void)		interrupt 1
{
	static unsigned int count;
	TL0 = 0x91;		
	TH0 = 0xff;		
	count++;
	if(count<high){DA=1;}
	else{DA=0;}
	count%=100;
}
