#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__
#include "stm32f10x.h"
#define SPI2_SCK_PORT GPIOB
#define SPI2_MOSI_PORT GPIOB
#define SPI2_MISO_PORT GPIOB

#define SPI2_SCK_PIN GPIO_Pin_13
#define SPI2_MOSI_PIN GPIO_Pin_15
#define SPI2_MISO_PIN GPIO_Pin_14

#define SPI2_SCK_CLK RCC_APB2Periph_GPIOB
#define SPI2_MISO_CLK RCC_APB2Periph_GPIOB
#define SPI2_MOSI_CLK RCC_APB2Periph_GPIOB

#define SPI2_TIME 0xFFFF

void SPI2_Init(void);
u8 SPI_RS(u8 Data);
#endif

