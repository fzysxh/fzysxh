#ifndef __XPT2046_H__
#define __XPT2046_H__
unsigned int xpt2046_read(unsigned char type); 
#define XP_8 0x9c  //0xbc
#define XP_12 0x94 //0xb4
#define YP_8 0xdc 
#define YP_12 0xd4
#define BAT_8 0xac
#define BAT_12 0xa4
#endif