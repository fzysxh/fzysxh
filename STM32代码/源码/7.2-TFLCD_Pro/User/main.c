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
	LCD_ShowStr_Color(0,0,"��һ����һ��û��ȥ�ɣ����ͨ���ˣ����ۣ������ָо�������ʹ��������~",Blue,BackColor);
	LCD_ShowStr_Color(0,48,"��һ����һ��û��ȥ�ɣ����ͨ���ˣ����ۣ������ָо�������ʹ��������~",Red,BackColor);
	LCD_ShowStr_Color(0,96,"��һ����һ��û��ȥ�ɣ����ͨ���ˣ����ۣ������ָо�������ʹ��������~",Green,BackColor);
	LCD_ShowStr_Color(0,144,"��һ����һ��û��ȥ�ɣ����ͨ���ˣ����ۣ������ָо�������ʹ��������~",Yellow,BackColor);
	LCD_ShowStr_Color(0,192,"��һ����һ��û��ȥ�ɣ����ͨ���ˣ����ۣ������ָо�������ʹ��������~",color1,BackColor);
	LCD_ShowStr_Color(0,240,"��һ����һ��û��ȥ�ɣ����ͨ���ˣ����ۣ������ָо�������ʹ��������~",color2,BackColor);
	LCD_ShowStr_Color(0,288,"I love you more than I can say,twice as much tomorrow,h ",color3,BackColor);
	while(1)
	{
		
	}
}



