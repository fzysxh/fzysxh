#include <reg52.h>
sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;
void delay(unsigned int i)
{
	while(i--);
}
void main()
{	while(1)

	{	led1=0;
		delay(50000);
		led2=0 ;
		delay(25000);
		led1=1;
		delay(50000);
		led3=0;
		delay(25000);
		led2=1;
		delay(10000);
		led4=0;
		delay(25000);
		led3=1;
		delay(10000);
		led4=1;
		delay(5000);

	 }
}