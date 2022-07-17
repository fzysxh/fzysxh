#ifndef __BSP_TIM_TPAD_H__
#define __BSP_TIM_TPAD_H__
#include <stm32f10x.h>
#include "delay.h"
void TIM_CAPTURE_Init(u16 div,u16 cnt);
void TPAD_Reset(void);
u16 TPAD_getval(void);
u16 TPAD_Init(void);
u8 logic(u8 mode,u8 times,u16 x);
#endif

