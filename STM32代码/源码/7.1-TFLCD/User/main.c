#include "stm32f10x.h"
#include "bsp_lcd_ili9341.h"
#include "usart.h"
#include "delay.h"
#include "usmart.h"
int main(void)
{
	delay_init();
	uart_init(115200);
	usmart_init(72);
	LCD_Init();
	LCD_DrawRecFull(60,0,100,130,0x0F0C);
	LCD_DrawRecFull(0,60,100,130,RGB888_TO_RGB565(187,64,129));
	LCD_DrawLine(0,0,240,320,FrontColor);
	LCD_ShowChar_EN(0,0,'a');
	LCD_ShowChar_EN(line(1),liney(2),'b');
	LCD_ShowChar_EN(line(1),liney(15),'c');
	lCD_ShowStr_EN(line(5),liney(19),"you've done a good job");
	while(1)
	{
	}
}



