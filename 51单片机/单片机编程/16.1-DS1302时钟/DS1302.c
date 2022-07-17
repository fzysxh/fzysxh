#include<regx52.h>
sbit CE = P3^5;
sbit IO = P3^4;
sbit SCLK = P3^6;
unsigned char code DS1302_Location[]={0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};
unsigned char DS1302_Data[]={00,37,23,03,12,05,21};//秒，分，时，日，月，周，年
void DS1302_Init()
{
	CE=0;
	SCLK=0;
}
unsigned char DS1302_Read(unsigned char command)//对应地址为写入操作地址，函数内部换为读取地址
{
	unsigned char i,Data=0x00;
	command|=0x01;
	CE=1;
	for(i=0;i<8;i++)
	{
		IO=command&(0x01<<i);
		SCLK=0;
		SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		SCLK=1;
		SCLK=0;
		if(IO) 
		{Data|=(0x01<<i);}
	}
  IO=0;
	CE=0;
	return Data;//BCD类型
}
//先写入指令，再写入字符
void DS1302_Write(unsigned char command,Data)
{
	unsigned char i;
	CE=1;
	for(i=0;i<8;i++)
	{
		IO=command&(0x01<<i);
		SCLK=1;
		SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		IO=Data&(0x01<<i);
		SCLK=1;
		SCLK=0;
	}
	CE=0;
	IO=0;
}
//接受时钟数据并储存再DS1302_Data[]中
void DS1302_Get()
{
	unsigned char i,a;
	for(i=0;i<7;i++)
	{
		a=DS1302_Read(DS1302_Location[i]);
		DS1302_Data[i]=(a/16)*10+a%16;
	}
}
//将DS1302_Data[]中数据写入时钟芯片,可通过更改DS1302_Data中数据调节时间
void DS1302_Set()
{
		unsigned char a,b,i;
	for(i=0;i<7;i++)
	{
		a=DS1302_Data[i];
		b=(a/10)*16+a%10;
		DS1302_Write(DS1302_Location[i],b);
	}
}
