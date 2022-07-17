#include<reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;
sbit fm=P1^5;
void delay(u8 i)
{
	while(i--);
}
void main()
{
	while(1)
	{
		if(k1==0)
		{	while(1)
		    {
				fm=~fm;
				delay(600);
				if(k1==1)
				break;
			}
		}	
		if(k2==0)
		{
			while(1)
		    {
				fm=~fm;
				delay(450);
				if(k2==1)
				break;
			}
		}
		if(k3==0)
		{
			while(1)
		    {
				fm=~fm;
				delay(300);
				if(k3==1)
				break;
			}
		}
		if(k4==0)
		{
			while(1)
		    {
				fm=~fm;
				delay(150);
				if(k4==1)
				break;
			}
		}		
	}
 }