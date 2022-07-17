#include<reg52.h>
#include"delay.h"
#include"LCD1602.h"
#include"XPT2046.h"
unsigned int a,b,c;
void main()
{
	LCD_Init();
 	LCD_ShowString(1,1,"TR   QR   LR");
	while(1)
	{
		a=xpt2046_read(XP_12);
		b=xpt2046_read(YP_12);
		c=xpt2046_read(BAT_12);
		LCD_ShowNum(2,1,a,4);
		LCD_ShowNum(2,6,b,4);
		LCD_ShowNum(2,11,c,4);
	}
}