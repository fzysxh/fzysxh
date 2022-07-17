#include "bsp_oled.h"
/*
���ܣ���OLED����һ���ֽ�,I2CͨѶ
  ���������
	1.����
	2.ģʽ��1Ϊд��ָ�0Ϊд������
  ���أ���
*/
void OLED_WriteByte(u8 Data,u8 mode)
{
	I2C_Star();
	I2C_WriteByte(OLED_Adr);
	I2C_RA();
	if(mode){I2C_WriteByte(0x00);}
	else{I2C_WriteByte(0x40);}
	I2C_RA();
	I2C_WriteByte(Data);
	I2C_RA();
	I2C_Stop();
}
/*
  ���ܣ�OLED��ʼ������ָ��ɳ����ṩ
  �����������
  ���أ���
*/
void OLDE_Init(void)
{
	delay_ms(200);
	OLED_WriteByte(0xAE,1);//--display off
	OLED_WriteByte(0x00,1);//---set low column address
	OLED_WriteByte(0x10,1);//---set high column address
	OLED_WriteByte(0x40,1);//--set start line address  
	OLED_WriteByte(0xB0,1);//--set page address
	OLED_WriteByte(0x81,1); // contract control
	OLED_WriteByte(0xFF,1);//--128   
	OLED_WriteByte(0xA1,1);//set segment remap 
	OLED_WriteByte(0xA6,1);//--normal / reverse
	OLED_WriteByte(0xA8,1);//--set multiplex ratio(1 to 64)
	OLED_WriteByte(0x3F,1);//--1/32 duty
	OLED_WriteByte(0xC8,1);//Com scan direction
	OLED_WriteByte(0xD3,1);//-set display offset
	OLED_WriteByte(0x00,1);//
	
	OLED_WriteByte(0xD5,1);//set osc division
	OLED_WriteByte(0x80,1);//
	
	OLED_WriteByte(0xD8,1);//set area color mode off
	OLED_WriteByte(0x05,1);//
	
	OLED_WriteByte(0xD9,1);//Set Pre-Charge Period
	OLED_WriteByte(0xF1,1);//
	
	OLED_WriteByte(0xDA,1);//set com pin configuartion
	OLED_WriteByte(0x12,1);//
	
	OLED_WriteByte(0xDB,1);//set Vcomh
	OLED_WriteByte(0x30,1);//
	
	OLED_WriteByte(0x8D,1);//set charge pump enable
	OLED_WriteByte(0x14,1);//
	
	OLED_WriteByte(0xAF,1);//--turn on oled panel

}
/*
  ���ܣ�������ʾ
  �����������
  ���أ���
*/
void OLED_On(void)
{
	OLED_WriteByte(0x8D,1);
	OLED_WriteByte(0x14,1);
	OLED_WriteByte(0xAF,1);
}
/*
  ���ܣ��ر���ʾ
  �����������
  ���أ���
*/
void OLED_OFF(void)
{
	OLED_WriteByte(0x8D,1);
	OLED_WriteByte(0x10,1);
	OLED_WriteByte(0xAE,1);
}
/*
  ���ܣ�������ȫ��
  �����������
  ���أ��� 
*/
void OLED_Clear(void)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_WriteByte(0xb0+i,1);
		OLED_WriteByte(0x00,1);
		OLED_WriteByte(0x10,1);
		for(j=0;j<128;j++)
		{
			OLED_WriteByte(0x00,0);
		}
	}
}
/*
  ���ܣ����ù��λ�ã�����ҳѰַģʽ
  �����������λ�ã�0-127����ҳλ�ã�0-7��
  ���أ���
*/
void OLED_SetPos(u8 x,u8 y)
{
	OLED_WriteByte(0xb0+y,1);
	OLED_WriteByte(0x0f&x,1);
	OLED_WriteByte(((0xf0&x)>>4)|0x10,1);
}
/*
  ���ܣ���ָ��λ����ʾһ��Ӣ���ַ�
  ���������
	1.�ַ����е�ַ
	2.�ַ���ҳ��ַ
	3.�ַ�
  ���أ���
*/
void OLED_ShowChar_EN(u8 x,u8 y,char a)
{
	u8 step,i;
	step=a-' ';
	OLED_SetPos(x,y);
	for(i=0;i<ASCALL_8X16.Width;i++)
	{
		OLED_WriteByte(*(ASCALL_8X16.table+16*step+i),0);
	}
	OLED_SetPos(x,y+1);
	for(i=0;i<ASCALL_8X16.Width;i++)
	{
		OLED_WriteByte(*(ASCALL_8X16.table+16*step+i+8),0);
	}
}
/*
  ���ܣ���ָ��λ����ʾ�ַ��������ߺ���һ����ʼ�����׺�ص����Ͻ�
  ���������
	1.�ַ���ʼ����е�ַ
	2.�ַ���ʼ���ҳ��ַ
	3.�ַ���
  ���أ���
*/
void OLED_ShowStr_EN(u8 x,u8 y,char * a)
{
	while(*a !='\0')
	{
		if(x>120)
		{
			x=0;
			y+=2;
			if(y>6)
			{y=0;}
		}
		OLED_ShowChar_EN(x,y,*a);
		x+=ASCALL_8X16.Width;
		a++;
	}
}


