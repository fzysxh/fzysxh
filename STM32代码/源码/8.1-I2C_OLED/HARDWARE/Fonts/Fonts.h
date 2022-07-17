#ifndef __FONTS_H__
#define __FONTS_H__
#include <stm32f10x.h>
typedef struct{
	const uint8_t * table;
	u8 Width;
	u8 Higth;
}Font;
extern Font ASCALL_8X16;
#endif





