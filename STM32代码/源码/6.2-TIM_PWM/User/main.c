#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_tim_pwm.h"
#include "sys.h"
#include "delay.h"
int main(void)
{
	u8 mode=1;
	u16 temp=200;
	TIM_PWM_Init(0,899);
	delay_init();
	LED_Init();
	while(1)
	{
		delay_ms(10);
		if(mode == 1){temp++;}
		else				 {temp--;}
		if(temp>800){mode=0;}
		if(temp<0){mode=1;}
		TIM_SetCompare2(TIM3,temp);
	}
}



