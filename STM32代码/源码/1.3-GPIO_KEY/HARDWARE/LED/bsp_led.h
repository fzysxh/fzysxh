#ifndef __BSP_LED_H__
#define __BSP_LED_H__
#include"stm32f10x.h"
void LED_Init(void);
#define LED_G_GPIO_PORT GPIOE
#define LED_R_GPIO_PORT GPIOB
#define LED_G_GPIO_PIN GPIO_Pin_5
#define LED_R_GPIO_PIN GPIO_Pin_5
#define LED_G_CLK RCC_APB2Periph_GPIOE
#define LED_R_CLK RCC_APB2Periph_GPIOB

#endif

