#include<regx52.h>
#include"delay.h"
#define LSA P2_2
#define LSB P2_3
#define LSC P2_4
typedef unsigned int u16;
typedef unsigned char u8;
void smgnumber(unsigned int which,what)
{
	u8 code smg[]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d, 0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,0x39 , 0x5e , 0x79 , 0x71 };
	switch(which)
			{
				case (8):
					LSA=0;LSB=0;LSC=0;break;
				case (7):
					LSA=1;LSB=0;LSC=0;break;
				case (6):
					LSA=0;LSB=1;LSC=0;break;
				case (5):
					LSA=1;LSB=1;LSC=0;break;
				case (4):
					LSA=0;LSB=0;LSC=1;break;
				case (3):
					LSA=1;LSB=0;LSC=1;break;
				case (2):
					LSA=0;LSB=1;LSC=1;		break;
				case (1):
					LSA=1;LSB=1;LSC=1;break;
			}
		switch(what)
				{
				  case(1):P0=smg[1];delay(1);P0=0x00;break;
					case(2):P0=smg[2];delay(1);P0=0x00;break;
					case(3):P0=smg[3];delay(1);P0=0x00;break;
					case(4):P0=smg[4];delay(1);P0=0x00;break;
					case(5):P0=smg[5];delay(1);P0=0x00;break;
					case(6):P0=smg[6];delay(1);P0=0x00;break;
					case(7):P0=smg[7];delay(1);P0=0x00;break;
					case(8):P0=smg[8];delay(1);P0=0x00;break;
					case(0):P0=smg[0];delay(1);P0=0x00;break;
				}
}