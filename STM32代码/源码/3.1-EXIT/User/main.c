#include "stm32f10x.h"
#include "bsp_key.h"
#include "bsp_exti.h"
#include "bsp_led.h"
#include "usart.h"
int main(void)
{
	delay_init();
	LED_Init();
	EXIT_Init();
	NVIC_init();
	KEY_Init();
	uart_init(115200);
	PEout(5)=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	while(1)
	{
		printf("oh my gosh!");
		delay_ms(1000);
	}
}



