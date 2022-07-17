#ifndef __BSP_LCD_ILI9341_H__
#define __BSP_LCD_ILI9341_H__
#include <stm32f10x.h>
#include "delay.h"
#include "bsp_flash.h"

#define ILI9341_CMD				*(__IO u16 *)0x6C000000
#define ILI9341_DATA			*(__IO u16 *)0x6C000800

#define BackColor	0x0000
#define FrontColor RGB888_TO_RGB565(255,255,255)
#define Blue RGB888_TO_RGB565(0,0,255)
#define Red RGB888_TO_RGB565(255,0,0)
#define Green RGB888_TO_RGB565(0,255,0)
#define Yellow RGB888_TO_RGB565(255,255,0)
#define color1 RGB888_TO_RGB565(16,224,208)
#define color2 RGB888_TO_RGB565(251,204,253)
#define color3 RGB888_TO_RGB565(129,65,175)
#define LongSide 320
#define ShortSide 240

#define ILI9341_CS_CLK	RCC_APB2Periph_GPIOG   
#define ILI9341_CS_PORT GPIOG
#define ILI9341_CS_Pin	GPIO_Pin_12

#define ILI9341_RS_CLK	RCC_APB2Periph_GPIOG  
#define ILI9341_RS_PORT GPIOG
#define ILI9341_RS_Pin	GPIO_Pin_0

#define ILI9341_WR_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_WR_PORT GPIOD
#define ILI9341_WR_Pin	GPIO_Pin_5

#define ILI9341_RD_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_RD_PORT GPIOD
#define ILI9341_RD_Pin	GPIO_Pin_4

//此处复位引脚与单片机复位引脚相连
//#define ILI9341_RST_CLK	RCC_APB2Periph_GPIOG   
//#define ILI9341_RST_PORT GPIOG
//#define ILI9341_RST_Pin	GPIO_Pin_12

#define ILI9341_BL_CLK	RCC_APB2Periph_GPIOB   
#define ILI9341_BL_PORT GPIOB
#define ILI9341_BL_Pin	GPIO_Pin_0

#define ILI9341_DB1_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_DB1_PORT GPIOD
#define ILI9341_DB1_Pin	GPIO_Pin_14

#define ILI9341_DB2_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_DB2_PORT GPIOD
#define ILI9341_DB2_Pin	GPIO_Pin_15

#define ILI9341_DB3_CLK	RCC_APB2Periph_GPIOD  
#define ILI9341_DB3_PORT GPIOD
#define ILI9341_DB3_Pin	GPIO_Pin_0

#define ILI9341_DB4_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_DB4_PORT GPIOD
#define ILI9341_DB4_Pin	GPIO_Pin_1

#define ILI9341_DB5_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB5_PORT GPIOE
#define ILI9341_DB5_Pin	GPIO_Pin_7

#define ILI9341_DB6_CLK	RCC_APB2Periph_GPIOE  
#define ILI9341_DB6_PORT GPIOE
#define ILI9341_DB6_Pin	GPIO_Pin_8

#define ILI9341_DB7_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB7_PORT GPIOE
#define ILI9341_DB7_Pin	GPIO_Pin_9

#define ILI9341_DB8_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB8_PORT GPIOE
#define ILI9341_DB8_Pin	GPIO_Pin_10

#define ILI9341_DB10_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB10_PORT GPIOE
#define ILI9341_DB10_Pin	GPIO_Pin_11

#define ILI9341_DB11_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB11_PORT GPIOE
#define ILI9341_DB11_Pin	GPIO_Pin_12

#define ILI9341_DB12_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB12_PORT GPIOE
#define ILI9341_DB12_Pin	GPIO_Pin_13

#define ILI9341_DB13_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB13_PORT GPIOE
#define ILI9341_DB13_Pin	GPIO_Pin_14

#define ILI9341_DB14_CLK	RCC_APB2Periph_GPIOE   
#define ILI9341_DB14_PORT GPIOE
#define ILI9341_DB14_Pin	GPIO_Pin_15

#define ILI9341_DB15_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_DB15_PORT GPIOD
#define ILI9341_DB15_Pin	GPIO_Pin_8

#define ILI9341_DB16_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_DB16_PORT GPIOD
#define ILI9341_DB16_Pin	GPIO_Pin_9

#define ILI9341_DB17_CLK	RCC_APB2Periph_GPIOD   
#define ILI9341_DB17_PORT GPIOD
#define ILI9341_DB17_Pin	GPIO_Pin_10

//输入RGB888对应RGB占比，输出不太准确的RGB565色彩值
#define RGB888_TO_RGB565(R,G,B) (uint16_t)((B/8)<<11)|((G/8)<<5)|(R/8)
#define line(x)	((x) * CurFont->Width)
#define liney(x) x * CurFont->Hight
void FSMC_Config(void);
void GPIO_Config(void);
void LCD_BL(FunctionalState State);
void LCD_Init(void);
void LCD_WriteData(u16 data);
void LCD_WriteCmd(u16 cmd);
u16 LCD_Read(void);
u16 LCD_ReadPixel(void);
u16 LCD_ReadId(void);
void LCD_SetCursor(u16 x,u16 y);
void LCD_Clear(u16 color);
void LCD_OpenWindow(u16 x,u16 y,u16 usWidth,u16 usHight);
void DrawPoint(u16 x,u16 y,u16 color);
void LCD_DrawLine(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_DrawRecFull(u16 x,u16 y,u16 usWidth,u16 usHight,u16 color);
void LCD_ShowCharCh(u16 x,u16 y,u16 word);
void LCD_ShowStr(u16 x,u16 y,u8 *pStr);
void LCD_ShowCharEn_Color(u16 x,u16 y,const char word,u16 Fcolor,u16 Bcolor);
void LCD_ShowCharCh_Color(u16 x,u16 y,u16 word,u16 Fcolor,u16 Bcolor);
void LCD_ShowStr_Color(u16 x,u16 y,u8 *pStr,u16 Fcolor,u16 Bcolor);
#endif

