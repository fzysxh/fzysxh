#ifndef __BSP_USART_H__
#define __BSP_USART_H__
#include <stm32f10x.h>
#include "stdio.h"	
#include "sys.h" 
void USART_NVIC_Init(void);
void My_USART_Init(uint32_t BaudRate);
void USART1_SendByte(USART_TypeDef * pUSARTx,uint8_t Byte);
void USART1_SendHalfWord(USART_TypeDef * pUSARTx,uint16_t Byte);
void USART1_SendArrary(USART_TypeDef * pUSARTx,uint8_t* arrary,uint8_t len);
void USART1_SendStr(USART_TypeDef * pUSARTx,char *str);
#endif


