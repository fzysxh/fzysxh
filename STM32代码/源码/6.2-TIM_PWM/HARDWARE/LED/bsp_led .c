#include"bsp_led.h"
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(LED_G_CLK|LED_R_CLK,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	GPIO_InitStruct.GPIO_Pin=LED_G_GPIO_PIN|LED_R_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_10MHz;
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_Init(LED_R_GPIO_PORT,&GPIO_InitStruct);
	GPIO_Init(LED_G_GPIO_PORT,&GPIO_InitStruct);
}


