#include<reg52.h>
#include<LCD1602.h>
#include"DS18B20.h"
void main()
{
	unsigned char L,H;
	int TT=0;
	float T=0;
	LCD_Init();
	LCD_ShowString(1,1,"Temperature:");
	while(1)
  {
		DS18B20_Init();           //开始操作
		DS18B20_WriteByte(0xcc); //ROM操作（跳过选择）
		DS18B20_WriteByte(0x44); //温度变化
		DS18B20_Init();          
		DS18B20_WriteByte(0xcc);
		DS18B20_WriteByte(0xbe);//写入读取操作
		L=DS18B20_ReceiveByte();//接受发来的两字节温度值
    H=DS18B20_ReceiveByte();
	  TT=(H<<8)|L; 
	  T=TT/16.0;
		if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(2,1,'-');	//显示负号
			T=-T;			//将温度变为正数
		}
		else				//如果温度大于等于0
		{
			LCD_ShowChar(2,1,'+');	//显示正号
		}
	  LCD_ShowNum(2,2,T,3);		//显示温度整数部分
		LCD_ShowChar(2,5,'.');		//显示小数点
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);//显示温度小数部分
	}
}