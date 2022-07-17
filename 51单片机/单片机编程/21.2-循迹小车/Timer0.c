#include<regx52.h>
void Timer0Init()		//100微秒
{
	
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初始值
	TH0 = 0xFF;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;	
}

//void Timer0(void)		interrupt 1
//{
//	static unsigned int count;
//	TL0 = 0x66;		
//	TH0 = 0xFC;		
//	count++;
//	if(count>1000)
//	{
//		count=0;
//		
//	}
//}
