#include<reg52.h>
sbit IN1=P0^1;
sbit IN2=P0^2;
sbit IN3=P0^3;
sbit IN4=P0^4;
void main()
{
	while(1)
	{
		IN1=1;
		IN2=0;
		IN3=1;
		IN4=0;
	}
}