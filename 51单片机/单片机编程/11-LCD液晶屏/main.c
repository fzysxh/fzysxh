#include<regx52.h>
#include<LCD1602.h>
#include<delay.h>
void main()
{
	LCD_Init();
	
	
	while(1)
	{
		LCD_ShowString(1,1,"sun xiaohui is ");
		LCD_ShowString(2,5,"so charming!");
		delay(4000);
		LCD_Init();
		LCD_ShowString(1,1,"she makes me");
		LCD_ShowString(2,5,"feel well");
		delay(4000);
		LCD_Init();
		LCD_ShowString(1,1,"I like her");
		delay(2000);
	}
}