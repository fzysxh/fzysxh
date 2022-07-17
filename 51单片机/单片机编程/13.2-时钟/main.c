#include<regx52.h>
#include"Timer0.h"
#include"LCD1602.h"
unsigned char Sec=0,Min=0,Hour=0;
void main()
{
	
	Timer0Init();
	LCD_Init();
	LCD_ShowString(1,1,"TIME:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}

void Timer0(void)		interrupt 1
{
	static unsigned int count;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	count++;
	if(count>=1000)
	{
		count=0;
		Sec++;
		if(Sec>=60)
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour>=24)
				{
					Hour=0;
				}
			}
		}
	}
	
	
	
}
