#include "bsp_spi.h"
//从机模式，引脚需要设置为输入模式
void SPI2_Init(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(SPI2_SCK_CLK|SPI2_MISO_CLK|SPI2_MOSI_CLK|SPI2_NSS_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=SPI2_SCK_PIN;
	GPIO_Init(SPI2_SCK_PORT,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=SPI2_MISO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(SPI2_MISO_PORT,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=SPI2_MOSI_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(SPI2_MOSI_PORT,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=SPI2_NSS_PIN;
	GPIO_Init(SPI2_NSS_PORT,&GPIO_InitStruct);
	//SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_CPOL=SPI_CPOL_High;
	SPI_InitStruct.SPI_CRCPolynomial=7;
	SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b ;
	SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode=SPI_Mode_Slave;
	SPI_InitStruct.SPI_NSS=SPI_NSS_Hard;
	
	SPI_Cmd(SPI2,ENABLE);
	SPI_Init(SPI2,&SPI_InitStruct);
}

u8 SPI_Read(void)
{
	u16 time=SPI2_TIME;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET)	
	{if(time--==0){return 0;}}
	SPI_I2S_ClearFlag(SPI2,SPI_I2S_IT_RXNE);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET)
	return SPI_I2S_ReceiveData(SPI2);
}
void SPI_Test(void)
{
	u16 time=SPI2_TIME;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET)	
	{if(time--==0){return;}}
	//printf("get char=%d",SPI_I2S_ReceiveData(SPI2));
	printf("get char from Jetson");
	while(1);
}




