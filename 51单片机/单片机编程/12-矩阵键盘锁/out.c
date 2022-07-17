#include <REGX52.H>
#include<delay.h>
typedef unsigned int u16;	  
typedef unsigned char u8;
u16 zhi=0;
#define KEY P1
u8 code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
/*
由1~9再涨
*/
int cs()
{
	zhi=0;
		KEY=0x0f;
		if(KEY!=0x0f)
		{
			delay(10);
				KEY=0x0f;
			switch(KEY)
			{
				case(0x0e):zhi=4;break;
	      case(0x0d):zhi=3;break;
		   	case(0x0b):zhi=2;break;
		  	case(0x07):zhi=1;break;
			}
				
			KEY=0xf0;
				switch(KEY)
				{
					case(0xe0):zhi+=12;break;
	        case(0xd0):zhi+=8;break;
		     	case(0xb0):zhi+=4;break;
		  	  case(0x70):zhi+=0;break;
				}
				while(KEY!=0xf0);
		} 
	
		return zhi;
}