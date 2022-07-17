#include "reg52.h"
#include "intrins.h"
#define led P2
sbit beep=P1^5;
void delay(unsigned int i)
{
	while(i--);
}
void main()
{
	int i;
	led=0xfe;
	delay(50000);
	while(1)
	{	
	 	for(i=0;i<7;i++)
		{
			P2=_crol_(P2,1);
			delay(50000);
		}
		for(i=0;i<7;i++)
		{
			P2=_cror_(P2,1);
			delay(50000);
		}
		for(i=0;i<1000;i++)
		{
			beep=~beep;
		delay(1000);
		}
	}
}