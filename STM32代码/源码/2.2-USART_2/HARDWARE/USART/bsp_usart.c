#include "bsp_usart.h"
//初始化NVIC
void USART_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_Init(&NVIC_InitStruct);
}
//初始化串口，此函数位USART1
void My_USART_Init(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_DeInit(USART1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	USART_InitStruct.USART_BaudRate=BaudRate;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode= USART_Mode_Rx| USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}
//串口中断服务函数
void USART1_IRQHandler(void)
{
	uint16_t rs;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		rs= USART_ReceiveData(USART1);
		USART_SendData(USART1,rs);
	}
}
//发送一个字节
void USART1_SendByte(USART_TypeDef * pUSARTx,uint8_t Byte)
{
	USART_SendData(pUSARTx,Byte);
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE)!=SET);
}
void USART1_SendHalfWord(USART_TypeDef * pUSARTx,uint16_t Byte)
{
	uint8_t temp_h;
	temp_h=(Byte&0xff00)>>8;
	USART_SendData(pUSARTx,temp_h);
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE)!=SET);
	USART_SendData(pUSARTx,Byte);
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE)!=SET);
}
//发送一个数组
void USART1_SendArrary(USART_TypeDef * pUSARTx,uint8_t * arrary,uint8_t len)
{
	uint8_t i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(pUSARTx,*(arrary++));
		while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE)!=SET);
	}
}
//发送字符串
void USART1_SendStr(USART_TypeDef * pUSARTx,char *str)
{
	uint8_t i=0;
	do
	{
		USART_SendData(pUSARTx,*(str+i));
		while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TXE)!=SET);
		i++;
	}while(*(str+i)!='\0');
}


