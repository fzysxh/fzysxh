#include<regx52.h>
#include"LCD1602.h"
#include"DS1302.h"
void main()
{
	DS1302_Init();
	LCD_Init();

  DS1302_Set();
	LCD_ShowString(1,1,"    -  -");
	LCD_ShowString(2,1," -  :  :");
	while(1)
	{
		DS1302_Get();
		LCD_ShowNum(1,1,20,2);
		LCD_ShowNum(1,3,DS1302_Data[6],2);
		LCD_ShowNum(1,6,DS1302_Data[4],2);
		LCD_ShowNum(1,9,DS1302_Data[3],2);
		LCD_ShowNum(2,1,DS1302_Data[5],1);
		LCD_ShowNum(2,3,DS1302_Data[2],2);
		LCD_ShowNum(2,6,DS1302_Data[1],2);
		LCD_ShowNum(2,9,DS1302_Data[0],2);
	}
}