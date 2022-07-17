#include "bsp_e2prom.h"
/*  
	AT2402的驱动，共有256个字节的空间，写地址为0xA0，读地址为0xA1
*/
/*
  功能：从指定地址读取一个字节
  传入参数：
	1.地址，0-255
  返回：指定地址的值
*/
u8 E2PROM_ReadByte(u8 Adr)
{
	u8 a;
	I2C_Star();  
	I2C_WriteByte(Write_Adr);//AT24C02写入指令
	I2C_RA();
	I2C_WriteByte(Adr);//要读取数据的位置
	I2C_RA();
	I2C_Star(); 
	I2C_WriteByte(Read_Adr);//读取指令
	I2C_RA();
	a=I2C_RecieveByte();
	I2C_NAck();
	I2C_Stop();
	return a;
}
/*
  功能：向指定地址写入数据
  传入参数：
	1.地址
	2.数据
  返回：无
*/
void E2PROM_WriteByte(u8 Adr,u8 Data)
{
	I2C_Star();  
	I2C_WriteByte(Write_Adr);//写入指令
	I2C_RA();
	I2C_WriteByte(Adr);//地址
	I2C_RA();
	I2C_WriteByte(Data);//数据
	I2C_RA();
	I2C_Stop();
	delay_ms(10);//给芯片预留时间完成写入，防止出错
}
/*
  功能：向指定地址写入字符串
  传入参数：
	1.写入地址
	2.字符串指针
  返回：无
*/
void E2PROM_WriteStr(u8 Adr,u8 * Str)
{
	while(*Str!='\0')
	{
		E2PROM_WriteByte(Adr,*Str);
		Adr++;
		Str++;
	}
}
/*
  功能：从指定地址开始地址递增的读取数据，存入给定数组中
  传入参数：
	1.地址
	2.字符串长度
	3.数组指针
  返回：无
*/
void E2PROM_ReadStr(u8 Adr,u8 len,u8 *Arr)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		*Arr=E2PROM_ReadByte(Adr);
		Arr++;
		Adr++;
	}
}

