#ifndef __BSP_E2PROM_H__
#define __BSP_E2PROM_H__
#include <stm32f10x.h>
#include "bsp_i2c.h"
#include "delay.h"
#define Read_Adr 0xA1
#define Write_Adr 0xA0
u8 E2PROM_ReadByte(u8 Adr);
void E2PROM_WriteByte(u8 Adr,u8 Data);
void E2PROM_ReadStr(u8 Adr,u8 len,u8 *Arr);
void E2PROM_WriteStr(u8 Adr,u8 * Str);
#endif



