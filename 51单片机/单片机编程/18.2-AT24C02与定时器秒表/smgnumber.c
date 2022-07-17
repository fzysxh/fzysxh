#include<regx52.h>
#include"delay.h"
#define LSA P2_2
#define LSB P2_3
#define LSC P2_4
typedef unsigned int u16;
typedef unsigned char u8;
unsigned char Time[]={0,1,2,16,2,3,16,5,9};
	u8 code smg[]={0x3f , 0x06, 0x5b , 0x4f , 0x66 , 0x6d, 0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,0x39 , 0x5e , 0x79 , 0x71,0x40};
void smgnumber(unsigned int which,what)
{
	P0=0x00;
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
			P0=smg[what];
}
void Smg_Loop()
{
	static unsigned char i;
	smgnumber(i,Time[i]);
	i++;
	if(i>8){i=1;}
}
void Smg_Table(unsigned char address,unsigned char Num)
{
	Time[address]=Num;
}