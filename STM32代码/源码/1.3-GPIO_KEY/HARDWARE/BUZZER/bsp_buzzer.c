#include "bsp_buzzer.h"
void BUZZER_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(BUZZER_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=BUZZER_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(BUZZER_GPIO_PORT,&GPIO_InitStruct);
	GPIO_ResetBits(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN);
}


