#include<reg52.h>
#include"independence_con.h"
#include"Timer0.h"
#include"smgnumber.h"
#include"I2C.h"
#include"AT24C02.h"
unsigned char Min,Sec,Msec,Run,T;
void main()
{
	Timer0Init();
	while(1)
	{
		T=Key();
		Smg_Table(1,Min/10);
		Smg_Table(2,Min%10);
		Smg_Table(4,Sec/10);
		Smg_Table(5,Sec%10);
		Smg_Table(7,Msec/10);
  	Smg_Table(8,Msec%10);
		if(T==1)
		{
			Run=!Run;
		}		
		if(T==2)
		{
			Min=0;
			Sec=0;
			Msec=0;
		}
		if(T==3)
		{
			AT24C02_Write(1,Min/10);
			AT24C02_Write(2,Min%10);
			AT24C02_Write(3,Sec/10);
			AT24C02_Write(4,Sec%10);
			AT24C02_Write(5,Msec/10);
			AT24C02_Write(6,Msec%10);
		}
		if(T==4)
		{
			AT24C02_Receive(1);
			AT24C02_Receive(2);
			AT24C02_Receive(3);
			AT24C02_Receive(4);
			AT24C02_Receive(5);
			AT24C02_Receive(6);
		}
	}
	
}
void SEC_Loop()
{
	if(Msec>99)
	{
		Msec=0;
		Sec++;
		if(Sec>59)
		{
			Sec=0;
			Min++;
			if(Min>99)
			{Min=0;}
		}
	}
}

void Timer0(void)		interrupt 1
{
	static unsigned int count1,count2,count3;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	count1++;
	if(count1>20)
	{
	  KEY_Loop();
		count1=0;
		
	}
	count2++;
	if(count2>1)
	{
		count2=0;
		Smg_Loop();
	}
	if(Run==0)
	{
	  count3++;
	  if(count3>9)
  	{
	  	count3=0;
	  	Msec++;
	  	SEC_Loop();
	  }		
	}
}
