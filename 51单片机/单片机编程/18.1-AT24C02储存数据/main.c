#include<reg52.h>
#include<I2C.h>
#include"AT24C02.h"
#include"LCD1602.h"
#include"independence_con.h"
#include"delay.h"
unsigned char KEY;
unsigned int Num;
void  main()
{
	LCD_Init();
	while(1)
	{
		LCD_ShowNum(1,1,Num,6);
		KEY=independent();
		if(KEY==1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,6);
		}
		if(KEY==2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,6);
		}
		if(KEY==3)
		{
			AT24C02_Write(1,Num/256);
			AT24C02_Write(2,Num%256);
		}
		if(KEY==4)
		{
			Num=AT24C02_Receive(2);
			Num|=AT24C02_Receive(1)<<8;
		}
	}
}