#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__
#include "stm32f10x.h"
#include "bsp_i2c.h"
#include "delay.h"
#include "Fonts.h"
#define OLED_Adr 0x78
void OLED_WriteByte(u8 Data,u8 mode);
void OLDE_Init(void);
void OLED_On(void);
void OLED_OFF(void);
void OLED_Clear(void);
void OLED_SetPos(u8 x,u8 y);
void OLED_ShowChar_EN(u8 x,u8 y,char a);
void OLED_ShowStr_EN(u8 x,u8 y,char * a);
#endif

