#include "stm32f10x.h"
#include "bsp_lcd_ili9341.h"
#include "usart.h"
#include "delay.h"
#include "usmart.h"
int main(void)
{
	delay_init();
	LCD_Init();
	FLASH_Init();
//	LCD_DrawRecFull(60,0,100,130,0x0F0C);
//	LCD_DrawRecFull(0,60,100,130,RGB888_TO_RGB565(187,64,129));
//	LCD_DrawLine(0,0,240,320,FrontColor);
	LCD_ShowStr_Color(0,0,"五一假期一天没出去成，光搞通信了，好累，但是又感觉还不错，痛并快乐着~",Blue,BackColor);
	LCD_ShowStr_Color(0,48,"五一假期一天没出去成，光搞通信了，好累，但是又感觉还不错，痛并快乐着~",Red,BackColor);
	LCD_ShowStr_Color(0,96,"五一假期一天没出去成，光搞通信了，好累，但是又感觉还不错，痛并快乐着~",Green,BackColor);
	LCD_ShowStr_Color(0,144,"五一假期一天没出去成，光搞通信了，好累，但是又感觉还不错，痛并快乐着~",Yellow,BackColor);
	LCD_ShowStr_Color(0,192,"五一假期一天没出去成，光搞通信了，好累，但是又感觉还不错，痛并快乐着~",color1,BackColor);
	LCD_ShowStr_Color(0,240,"五一假期一天没出去成，光搞通信了，好累，但是又感觉还不错，痛并快乐着~",color2,BackColor);
	LCD_ShowStr_Color(0,288,"I love you more than I can say,twice as much tomorrow,h ",color3,BackColor);
	while(1)
	{
		
	}
}



