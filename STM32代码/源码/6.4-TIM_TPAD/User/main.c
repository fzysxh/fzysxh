#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_tim_tpad.h"
#include "sys.h"
//程序启动之初会读取电容充电时间，复位后短暂时间内
//触摸电容按键可能会导致程序异常
int main(void)
{
	u16 temp;
	TIM_CAPTURE_Init(71,0xFFFF);
	delay_init();
	temp=TPAD_Init();
	LED_Init();
	while(1)
	{
		if(logic(0,temp,3)==1)
		{
			PEout(5)=!PEout(5);
		}
	}
}



