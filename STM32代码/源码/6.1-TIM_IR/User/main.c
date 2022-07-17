#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_tim_ir.h"
int main(void)
{
	TIM_Ir_Init();
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	GPIOE->ODR&~(1<<5);
	while(1)
	{
		
	}
}



