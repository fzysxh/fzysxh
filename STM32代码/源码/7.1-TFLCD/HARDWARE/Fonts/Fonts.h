#ifndef __FONTS_H__
#define __FONTS_H__
#include <stm32f10x.h>
extern const uint8_t ASCII8x16_Table [ ];
typedef struct
{
	const uint8_t * Table;
	u16 Width;
	u16 Hight;
}Font_Table;
extern Font_Table Font_8x16;

#endif


