#include "bsp_i2c.h"
void I2c_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(I2C_SCL_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(I2C_SDA_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin=I2C_SCL_Pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(I2C_SCL_PORT,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=I2C_SDA_Pin;
	GPIO_Init(I2C_SDA_PORT,&GPIO_InitStruct);
}
void I2C_Delay()
{
	u8 i;
	for(i=0;i<10;i++);
}
void I2C_Star()
{
	I2C_SCL_1;
	I2C_SDA_1;
	I2C_Delay();
	I2C_SDA_0;
	I2C_Delay(); 
	I2C_SCL_0; 
}
void I2C_Stop()
{
	I2C_SDA_0;
	I2C_SCL_1;
	I2C_Delay();
	I2C_SDA_1;
}
//发送应答
void I2C_Ack()
{
	I2C_SDA_0;
	I2C_SCL_0;
	I2C_Delay();
	I2C_SCL_1;
	I2C_Delay();
	I2C_SDA_0;
	I2C_Delay();
}
void I2C_NAck()
{
	I2C_SCL_0;
	I2C_SDA_1;
	I2C_Delay();
	I2C_SCL_1;
	I2C_Delay();
	I2C_SDA_0;
}
//接收应答，0为应答
u8 I2C_RA()
{
	u8 y;
	I2C_SDA_1;
	I2C_SCL_1;
	I2C_Delay();
	y=I2C_Get_SDA;
	I2C_Delay();
	I2C_SCL_0;
	return y;
}
void I2C_WriteByte(u8 Data)
{
	u8 i;
	I2C_SCL_0;
	for(i=0;i<8;i++)
	{
		if(Data&(0x80>>i)){I2C_SDA_1;}
		else{I2C_SDA_0;}
		I2C_Delay();
		I2C_SCL_1;
		I2C_Delay();
		I2C_SCL_0;
	}
	I2C_SDA_1;
}
u8 I2C_RecieveByte()
{
	u8 i,data=0;
	I2C_SDA_1;
	for(i=0;i<8;i++)
	{
		I2C_SCL_0;
		I2C_Delay();
		I2C_SCL_1;
		if(I2C_Get_SDA)
		{data|=(0x80>>i);}
		I2C_Delay();		
	}
	return data;
}


