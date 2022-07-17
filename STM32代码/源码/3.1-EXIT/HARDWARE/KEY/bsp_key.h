#ifndef __BSP_KEY_H__
#define __BSP_KEY_H
#include "stm32f10x.h"
#define KEY_1_GPIO_PORT GPIOE
#define KEY_0_GPIO_PORT GPIOE
#define KEY_WK_GPIO_PORT GPIOA
#define KEY_1_GPIO_PIN GPIO_Pin_3
#define KEY_0_GPIO_PIN GPIO_Pin_4
#define KEY_WK_GPIO_PIN GPIO_Pin_0
#define KEY_1_CLK RCC_APB2Periph_GPIOE
#define KEY_0_CLK RCC_APB2Periph_GPIOE
#define KEY_WK_CLK RCC_APB2Periph_GPIOA
void KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);
#endif



