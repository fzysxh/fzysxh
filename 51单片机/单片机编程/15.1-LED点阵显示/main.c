#include<regx52.h>
#include"_74HC595.h"
#include"MLED.h"
unsigned char code smg[]={0x89,0xBF,0xC8,0x80,0x04,0x08,0xFF,0x08};
unsigned char i;
void main()
{
	while(1)
	{
		for(i=0;i<8;i++)
		{
			MLED(i,smg[i]);
		}
	}
}