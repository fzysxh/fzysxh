#include <regx52.h>
#include <intrins.h>
#include"delay.h"
#include"independence_con.h"
typedef unsigned int u16;
typedef unsigned char u8;
void main()
{
	
	u8 KEY,Temp=0x00;
	P2=0xff;
	while(1)
	{
		KEY=independent();
	  if(KEY)
	  {
		  Temp++;
		  P2=~Temp;
	  }
	}
	
}