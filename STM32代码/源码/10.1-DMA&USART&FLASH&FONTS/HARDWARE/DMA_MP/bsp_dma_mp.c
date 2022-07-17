#include "bsp_dma_mp.h"
#include "bsp_usart.h"
extern uint8_t arr[2048];
/* 
��Ҫ���������ж�
*/
void DMA_MP_Confg(uint32_t m_add,uint32_t p_add,DMA_Channel_TypeDef * CHANEL,uint16_t size)
{
	
	DMA_InitTypeDef DMA_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	//ʹ��     **DMA1**    ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//�����ڴ�������ַ
	DMA_InitStruct.DMA_PeripheralBaseAddr=p_add;
	DMA_InitStruct.DMA_MemoryBaseAddr=m_add;
	//ģʽ����λ�����赽�ڴ�
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;
	//����������
	DMA_InitStruct.DMA_BufferSize=size;
	//�������������ģʽ���ڴ�λ����ģʽ
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	//�����ڴ���������ݴ�С
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	//ѭ��ģʽ
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
	//�������ȼ�
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	//���ڴ浽�ڴ�ģʽ
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	//��ʼ��ͨ��
	DMA_Init(CHANEL,&DMA_InitStruct);
	
	
	//ʹ��DMA��������жϺ��������ж�
	DMA_ITConfig(CHANEL,DMA_IT_TC,ENABLE);
	DMA_ITConfig(CHANEL,DMA_IT_HT,ENABLE);
	
	//���ô��ں�DMA�ж�
	NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	//ʹ��DMAĳCHANEL
	DMA_Cmd(CHANEL,ENABLE);
}




