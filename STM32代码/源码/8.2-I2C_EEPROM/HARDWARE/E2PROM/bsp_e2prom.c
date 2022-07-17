#include "bsp_e2prom.h"
/*  
	AT2402������������256���ֽڵĿռ䣬д��ַΪ0xA0������ַΪ0xA1
*/
/*
  ���ܣ���ָ����ַ��ȡһ���ֽ�
  ���������
	1.��ַ��0-255
  ���أ�ָ����ַ��ֵ
*/
u8 E2PROM_ReadByte(u8 Adr)
{
	u8 a;
	I2C_Star();  
	I2C_WriteByte(Write_Adr);//AT24C02д��ָ��
	I2C_RA();
	I2C_WriteByte(Adr);//Ҫ��ȡ���ݵ�λ��
	I2C_RA();
	I2C_Star(); 
	I2C_WriteByte(Read_Adr);//��ȡָ��
	I2C_RA();
	a=I2C_RecieveByte();
	I2C_NAck();
	I2C_Stop();
	return a;
}
/*
  ���ܣ���ָ����ַд������
  ���������
	1.��ַ
	2.����
  ���أ���
*/
void E2PROM_WriteByte(u8 Adr,u8 Data)
{
	I2C_Star();  
	I2C_WriteByte(Write_Adr);//д��ָ��
	I2C_RA();
	I2C_WriteByte(Adr);//��ַ
	I2C_RA();
	I2C_WriteByte(Data);//����
	I2C_RA();
	I2C_Stop();
	delay_ms(10);//��оƬԤ��ʱ�����д�룬��ֹ����
}
/*
  ���ܣ���ָ����ַд���ַ���
  ���������
	1.д���ַ
	2.�ַ���ָ��
  ���أ���
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
  ���ܣ���ָ����ַ��ʼ��ַ�����Ķ�ȡ���ݣ��������������
  ���������
	1.��ַ
	2.�ַ�������
	3.����ָ��
  ���أ���
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

