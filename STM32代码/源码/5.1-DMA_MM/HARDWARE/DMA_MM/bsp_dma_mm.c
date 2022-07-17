#include "bsp_dma_mm.h"
const uint32_t Flash_Const_Buffer[9]={0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,0x21222324};
uint32_t SRAM_BUFFER[9];
void DMA_MM_Confg(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_InitStruct.DMA_BufferSize=32;
	DMA_InitStruct.DMA_DIR =DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_M2M =DMA_M2M_Enable;
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)SRAM_BUFFER;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)Flash_Const_Buffer;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_Priority=DMA_Priority_High;
	DMA_Init(DMA1_Channel6,&DMA_InitStruct);
	DMA_ClearFlag(DMA1_FLAG_TC6);
	DMA_Cmd(DMA1_Channel6,ENABLE);
}
uint8_t check(const uint32_t* p1,uint32_t* p2,uint8_t len)
{
	for(;len>0;len--)
	{
		if(*(p1+len-1)!=*(p2+len-1)){return 0;}
	}
	return 1;
}

