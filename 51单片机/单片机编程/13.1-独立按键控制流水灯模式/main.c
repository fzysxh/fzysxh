#include<regx52.h>
#include"independence_con.h"
#include<Intrins.h>
#include"Timer0.h"
char mode,a;

void main()
{
  Timer0Init();
	P2=0xFE;
	while(1)
	{
		 a=independent();
		if(a)
		{
			mode++;
			if(mode>=2)
				mode=0;
		}
	}
}
void Timer0(void)		interrupt 1
{
	static unsigned int count;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	count++;
	if(count>1000)
	{
		count=0;
		if(mode==0)
			P2=_crol_(P2,1);
		if(mode==1)
			P2=_cror_(P2,1);
	}
}
