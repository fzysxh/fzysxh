#include "bsp_dma_mp.h"
#include "bsp_usart.h"
extern uint8_t arr[2048];
/* 
需要自行设置中断
*/
void DMA_MP_Confg(uint32_t m_add,uint32_t p_add,DMA_Channel_TypeDef * CHANEL,uint16_t size)
{
	
	DMA_InitTypeDef DMA_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	//使能     **DMA1**    时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//设置内存和外设地址
	DMA_InitStruct.DMA_PeripheralBaseAddr=p_add;
	DMA_InitStruct.DMA_MemoryBaseAddr=m_add;
	//模式设置位由外设到内存
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;
	//设置数据量
	DMA_InitStruct.DMA_BufferSize=size;
	//设置外设非增量模式，内存位增量模式
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	//设置内存外设的数据大小
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	//循环模式
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
	//设置优先级
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	//非内存到内存模式
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	//初始化通道
	DMA_Init(CHANEL,&DMA_InitStruct);
	
	
	//使能DMA传输完成中断和条过半中断
	DMA_ITConfig(CHANEL,DMA_IT_TC,ENABLE);
	DMA_ITConfig(CHANEL,DMA_IT_HT,ENABLE);
	
	//配置串口和DMA中断
	NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	//使能DMA某CHANEL
	DMA_Cmd(CHANEL,ENABLE);
}




