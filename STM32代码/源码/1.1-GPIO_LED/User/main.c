#include "stm32f10x.h"
#include "bsp_led.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  delay_init();
	uart_init(115200);	
	RCC_APB2PeriphClockCmd(LED_G_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=LED_G_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP ;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_10MHz;
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStruct);
	
	while(1)
	{
		printf("suprise?");
		delay_ms(100);
	}
}



