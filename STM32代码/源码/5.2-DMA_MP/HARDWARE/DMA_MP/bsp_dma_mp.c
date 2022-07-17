#include "bsp_dma_mp.h"

/* 
  * 配置DMA，由内部存储到串口转移数据
	* 内存递增模式，外设非递增
	* 仅支持双方数据大小一字节
	* 初始化未使能DMA
	*非循环模式
	para1:32位的内部数据地址
	para2:32位寄存器地址
	para3:DMA通道
	para4:数据量，最大位65535
*/
void DMA_MP_Confg(uint32_t m_add,uint32_t p_add,DMA_Channel_TypeDef * CHANEL,uint16_t size)
{
	
	DMA_InitTypeDef DMA_InitStruct;
	//使能     **DMA1**    时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//设置内存和外设地址
	DMA_InitStruct.DMA_PeripheralBaseAddr=p_add;
	DMA_InitStruct.DMA_MemoryBaseAddr=m_add;
	//模式设置位由内存到外设
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralDST;
	//设置数据量
	DMA_InitStruct.DMA_BufferSize=size;
	//设置外设非增量模式，内存位增量模式
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	//设置内存外村的数据大小
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	//非循环模式
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
	//设置优先级
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	//非内存到内存模式
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	//初始化通道
	DMA_Init(CHANEL,&DMA_InitStruct);
	//未使能
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
}



