#include <reg52.h>
sbit fmq=P1^5;
void delay(unsigned int i)
{
	while(i--);
}
void main()
{
	while(1)
	{
		fmq=~fmq;
		delay(150);	
	}
}
