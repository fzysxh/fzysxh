#include<regx52.h>
#include"_74HC595.h"
#include"delay.h"
#define M_LED P0
/*
brief:输出第P列，显示为D对应
    come_in:
    out:
*/
void MLED(unsigned char P,D)
{
	_74HC595(D);
	M_LED=~(0x80>>P);
	delay(1);
	M_LED=0xff;
}	
