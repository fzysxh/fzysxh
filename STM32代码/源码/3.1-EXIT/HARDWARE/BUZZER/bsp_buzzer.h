#ifndef __BSP_BUZZER_H__
#define __BSP_BUZZER_H__
#include "stm32f10x.h"
void BUZZER_Init(void);
#define BUZZER_GPIO_PORT GPIOB
#define BUZZER_GPIO_PIN GPIO_Pin_8
#define BUZZER_CLK RCC_APB2Periph_GPIOB
#endif 


