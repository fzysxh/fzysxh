#include "bsp_flash.h"
//�����ݴ�FLASH���ݣ�ʵ���м��д��
u8 FLASH_Temp[SectorSize];
/*
  ���ܣ���ʼ��FLASH������SPI�ĳ�ʼ��
  �����������
  ���أ���
*/
void FLASH_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	SPI2_Init();
}
/*
  ���ܣ�ʹFLASH������ܺ�ģʽ
  ���������
	1.
  ���أ�
*/
void FLASH_PowerDown(void)
{
	FLASH_Low;
	SPI_RS(W25X_PowerDown);
	FLASH_High;
}
/*
  ���ܣ�����͹���ģʽ
  ���������
	1.
  ���أ�
*/
void FLASH_Relase(void)
{
	FLASH_Low;
	SPI_RS(W25X_ReleasePowerDown);
	FLASH_High;
}
/*
  ���ܣ���ȡFLASH��ID��
  ���������
	1.
  ���أ�FLASH ID��
*/
u32 FLASH_Read_ID(void)
{
	u32 TID=0;
	FLASH_Low;
	SPI_RS(0x9F);
	TID|=(SPI_RS(0x00)<<16);
	TID|=(SPI_RS(0x00)<<8);
	TID|=SPI_RS(0x00);
	FLASH_High;
	return TID;
}
/*
  ���ܣ�FLASHдʹ��
  ���������
	1.
  ���أ�
*/
void FLASH_Write_ENABLE(void)
{
	FLASH_Low;
	SPI_RS(W25X_WriteEnable);
	FLASH_High;
}
/*
  ���ܣ��ر�дʹ��
  ���������
	1.
  ���أ�
*/
void FLASH_Write_DISABLE(void)
{
	FLASH_Low;
	SPI_RS(W25X_WriteDisable);
	FLASH_High;
}
/*
  ���ܣ��ȴ���FLASH��æ����
  ���������
	1.
  ���أ�
*/
void FLASH_Wait_Busy(void)
{
	u8 i=0;
	FLASH_Low;
	SPI_RS(W25X_ReadStatusReg);
	do
	{i=SPI_RS(0xFF);}while(i&0x01);
	FLASH_High;
}
/*
  ���ܣ�������ǰ��ַ����һ�����������ݣ����Ȳ���4096�ֽ�
  ���������
	1.��ʼ��ַ
  ���أ���
*/
void FLASH_ERASE_SECTOR(u32 Adr)
{
	FLASH_Write_ENABLE();
	FLASH_Wait_Busy(); 
	FLASH_Low;
	SPI_RS(W25X_SectorErase);
	SPI_RS((Adr>>16)&0xff);
	SPI_RS((Adr>>8)&0xff);
	SPI_RS(Adr&0xff);
	FLASH_High; 
}
/*
  ���ܣ����������������ǰ��ַ���ڿ����Ϣ��һ��64KB����254��
  ���������
	1.��ʼ��ַ
  ���أ�
*/
void FLASH_ERASE_BLOCK(u32 Adr)
{
	FLASH_Write_ENABLE();
	FLASH_Wait_Busy(); 
	FLASH_Low;
	SPI_RS(W25X_BlockErase);
	SPI_RS((Adr>>16)&0xff);
	SPI_RS((Adr>>8)&0xff);
	SPI_RS(Adr&0xff);
	FLASH_High; 
}
/*
  ���ܣ�ȫƬ����
  ���������
	1.
  ���أ�
*/
void FLASH_ERASE_ALL(void)
{
	FLASH_Write_ENABLE();
	FLASH_Wait_Busy(); 
	FLASH_Low;
	SPI_RS(W25X_ChipErase);
	FLASH_High; 	
}
/*
  ���ܣ���ȡָ����ַ��һ���ֽ�
  ���������
	1.��ȡ�ĵ�ַ
  ���أ��õ�ַ��Ӧһ���ֽڵ���Ϣ
*/
u8 FLASH_ReadByte(u32 Adr)
{
	u8 temp=0;
	FLASH_Wait_Busy();
	FLASH_Low;
	SPI_RS(W25X_ReadData);
	SPI_RS((Adr>>16)&0xff);
	SPI_RS((Adr>>8)&0xff);
	SPI_RS(Adr&0xff);
	temp=SPI_RS(0xff);
	FLASH_High;
	return temp;
}
/*
  ���ܣ�������ȡ������ָ������
  ���������
	1.��ȡ�ĵ�ַ
  2.����ָ��
	3.��ȡ����
  ���أ�
*/
void FLASH_Read_Arr(u32 Adr,u8 * Arr,u16 len)  
{
	u16 i;
	FLASH_Wait_Busy();
	FLASH_Low;
	SPI_RS(W25X_ReadData);
	SPI_RS((Adr>>16)&0xff);
	SPI_RS((Adr>>8)&0xff);
	SPI_RS(Adr&0xff);
	for(i=0;i<len;i++)
	{*Arr=SPI_RS(0xff);Arr++;}
	FLASH_High;
}
/*
  ���ܣ����ֽ�д��
  ���������
	1.д���ַ
	2.д�����Ϣ
  ���أ�
*/
void FLASH_WriteByte(u32 Adr,u8 Data)
{
	FLASH_Wait_Busy();
	FLASH_Write_ENABLE();
	FLASH_Low;
	SPI_RS(W25X_PageProgram);
	SPI_RS((Adr>>16)&0xff);
	SPI_RS((Adr>>8)&0xff);
	SPI_RS(Adr&0xff);
	SPI_RS(Data);
	FLASH_High;
}
/*
  ���ܣ��޼��ҳд�룬���д��256�ֽڣ�ֻ���ڵ�ǰҳ����
  ���������
	1.д�����ʼ��ַ
	2.д�������ָ��
	3.д����Ŀ
  ���أ�
*/
void FLASH_WritePage_NoCheck(u32 Adr,u8 *Arr,u16 len)
{
	u16 i=0;
	FLASH_Wait_Busy();
	FLASH_Write_ENABLE();
	FLASH_Low;
	SPI_RS(W25X_PageProgram);
	SPI_RS((Adr>>16)&0xff);
	SPI_RS((Adr>>8)&0xff);
	SPI_RS(Adr&0xff);
	for(i=0;i<len;i++)
	{SPI_RS(*Arr);Arr++;}
	FLASH_High;
}
/*
  ���ܣ��޼������д�룬���65535���ֽ�
  ���������
	1.��ʼ��ַ
	2.д�����ݵ������ָ��
	3.д����Ŀ
  ���أ�
*/
void FLASH_Write_NoCheck(u32 Adr,u8 *Arr,u16 len)
{
	u16 Leave_Byte,Leave,Leave_Page,i;
	Leave=PageSize-Adr%PageSize;
	Leave_Byte=(len-Leave)%PageSize;
	Leave_Page=(len-Leave)/PageSize;
	FLASH_Wait_Busy();
	FLASH_Write_ENABLE();
	if(len<Leave)
	{Leave=len;Leave_Byte=0;Leave_Page=0;}
		FLASH_WritePage_NoCheck(Adr,Arr,Leave);
		FLASH_Wait_Busy();
		for(i=0;i<Leave_Page;i++)
		{FLASH_WritePage_NoCheck(Adr+Leave+i*PageSize,Arr+Leave+i*PageSize ,PageSize);FLASH_Wait_Busy();}
		FLASH_WritePage_NoCheck(Adr+Leave+Leave_Page*PageSize,Arr+Leave+Leave_Page*PageSize,Leave_Byte);
}
/*
  ���ܣ��м������д�����Ѿ���д������ֽڲ�����д��
  ���������
	1.��ʼ��ַ
	2.д�����ݵ�����ָ��
  ���أ�
*/
void FLASH_Write_Check(u32 Adr,u8 *Arr,u16 len)   
{
	u16 Leave,i,j,Leave_Byte,Leave_Sector,off;
		Leave=SectorSize-Adr%SectorSize;
		off=Adr%SectorSize;
		Leave_Byte=(len-Leave)%SectorSize;
		Leave_Sector=(len-Leave)/SectorSize;
		FLASH_Write_ENABLE();	
		//////////////////////////////////////////////////////////////////////////
		if(len<Leave)
		{Leave=len;Leave_Byte=0;Leave_Sector=0;}
			FLASH_Read_Arr(Adr-off,FLASH_Temp,SectorSize);
			for(i=0;i<Leave;i++)
			{
				if(FLASH_Temp[i+off]!=0xFF)
				{
					FLASH_ERASE_SECTOR(Adr);
					for(j=0;j<Leave;j++)
					{
						FLASH_Temp[j+off]=*(Arr+j);
					}
					FLASH_Write_NoCheck(Adr-off,FLASH_Temp,SectorSize);
					break;
				}
			}
			if(i==Leave){FLASH_Write_NoCheck(Adr,Arr,Leave);}
			/////////////////////////////////////////////////////////////////////////
			
			for(i=0;i<Leave_Sector;i++)
			{
				FLASH_Read_Arr(Adr+Leave+i*SectorSize,FLASH_Temp,SectorSize);
				
				for(j=0;j<SectorSize;j++)
				{
					if(FLASH_Temp[j]!=0xFF)
					{
						FLASH_ERASE_SECTOR(Adr+Leave+i*SectorSize);
						FLASH_Write_NoCheck(Adr+Leave+i*SectorSize,Arr+Leave+i*SectorSize,SectorSize);
						break;
					}
				}
				if(j==SectorSize){FLASH_Write_NoCheck(Adr+Leave+i*SectorSize,Arr+Leave+i*SectorSize,SectorSize);}
			}
			/////////////////////////////////////////////////////////////////////////
			FLASH_Wait_Busy();
			FLASH_Read_Arr(Adr+Leave+SectorSize*Leave_Sector,FLASH_Temp,SectorSize);
			for(i=0;i<Leave_Byte;i++)
			{
				if(FLASH_Temp[i]!=0xFF)
				{
					FLASH_ERASE_SECTOR(Adr+Leave+SectorSize*Leave_Sector);
					for(j=0;j<Leave_Byte;j++)
					{
						FLASH_Temp[j]=*(Arr+j+Leave+SectorSize*Leave_Sector);
					}
					FLASH_Write_NoCheck(Adr+Leave+SectorSize*Leave_Sector,FLASH_Temp,SectorSize);
					break;
				}
			}
			if(i==Leave_Byte){FLASH_Write_NoCheck(Adr+Leave+Leave_Sector*SectorSize,Arr+Leave+Leave_Sector*SectorSize,Leave_Byte);}
}




