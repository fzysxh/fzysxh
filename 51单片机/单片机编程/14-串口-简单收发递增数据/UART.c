#include<regx52.h>
/*
    brief:初始化函数，发送数据函数，接受中断模板
    come_in:
    out:
*/
void UART_Init()//9600bps@11.0592MHz
{
	SCON=0x50;
	PCON|=0x80;	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器中断
	TR1 = 1;		//定时器1开始计时
	EA=1;//允许UART中断
	ES=1;
}
void SendByte(Byte)
{
	
		SBUF=Byte;
  	while(TI==0);
		TI=0;
}	
//void RecieveByte() interrupt 4
//{
//	if(RI==1)
//	{
//		
//		RI=0;
//	}
//}
