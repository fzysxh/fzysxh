#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_wwdg.h"
#include "sys.h"
#include "delay.h"
int main(void)
{
	LED_Init();
	delay_init();
	WWDG_Init(0x7f,0x5f,WWDG_Prescaler_8);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_ms(1000);
	while(1)
	{
		PBout(5)=1;
	}
	
}



