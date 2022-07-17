#include "stm32f10x.h"
#include "bsp_oled.h"
#include "delay.h"
/*本程序为OLED的驱动程序，驱动芯片为SSD1315*/
int main(void)
{
	delay_init();
	I2c_Init();
	OLDE_Init();
	OLED_Clear();
	OLED_ShowChar_EN(56,4,'a');
	OLED_ShowStr_EN(0,0,"That's too bad!");
	OLED_ShowStr_EN(0,2,"ni chong Qbi ma?");
	while(1)
	{
		
	}
}



