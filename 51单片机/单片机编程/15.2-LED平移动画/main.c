#include<regx52.h>
#include"MLED.h"
#include"Timer0.h"
/*
    brief:LED点阵显示跳动的心 
    come_in:
    out:
*/
unsigned char code smg[]={0x00,0x00,0x78,0x7C,0x3E,0x3E,0x7C,0x78,0x00,0x00};
unsigned char code smg2[]={0x00,0xF0,0xF8,0x7C,0x7C,0xF8,0xF0,0x00};
unsigned char code smg3[]={0x00,0x3C,0x3E,0x1F,0x1F,0x3E,0x3C,0x00};
unsigned char i,a;
void main()
{
	Timer0Init();
	
	while(1)
	{
		if(a==0)
		{
			for(i=0;i<8;i++)
			{
				MLED(i,smg[i+1]);
			}
		}
		if(a==1)
		{
			for(i=0;i<8;i++)
			{
				MLED(i,smg[i]);
			}
		}
		if(a==2)
		{
			for(i=0;i<8;i++)
			{
				MLED(i,smg2[i]);
			}
		}
		if(a==3)
		{
			for(i=0;i<8;i++)
			{
				MLED(i,smg[i+2]);
			}
		}
		if(a==4)
		{
			for(i=0;i<8;i++)
			{
				MLED(i,smg3[i]);
			}
		}
		
		
	
		
	}
}
void Timer0(void)		interrupt 1
{
	static unsigned long int count;//使用char可能达不到一千，不会执行if语句
	TL0 = 0x66;		
	TH0 = 0xFC;		
	count++;
	if(count>1000)
	{
		a++;
		if(a>4)
		{a=0;}
			
		count=0;
	}
}
