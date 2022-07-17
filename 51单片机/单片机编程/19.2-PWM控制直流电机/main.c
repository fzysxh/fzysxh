#include<regx52.h>
#include"Timer0.h"
#include"smgnumber.h"
#include"independence_con.h"
unsigned char T,D=0;
unsigned char KEY;
void main()
{
	
	Timer0Init();
	while(1)
	{
		KEY=independent();	
		if(KEY==1)
	  {
		  D++;
	  	D%=4;
	  	if(D==0){T=0;}
		  if(D==1){T=33;}
		  if(D==2){T=66;}
	  	if(D==3){T=99;}
	  }
	   smgnumber(1,D);
	}
	
}
void Timer0(void)		interrupt 1    //100微秒
{
	static unsigned int count;
	TL0 = 0xAE;		
  TH0 = 0xFB;		
	count++;
	count%=100;
	if(count<T){P1_0=1;}
	if(count>=T){P1_0=0;}
}
