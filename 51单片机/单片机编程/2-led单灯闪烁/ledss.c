#include <reg52.h>
sbit led1=P2^0;
void delay(unsigned int i)
{
	while(i--);
}
void main()
{	while(1)

	{	led1=0;
		delay(50000);
		led1=1;
		delay(50000);
	 }
}