#include "bsp_dma_mp.h"

/* 
  * ����DMA�����ڲ��洢������ת������
	* �ڴ����ģʽ������ǵ���
	* ��֧��˫�����ݴ�Сһ�ֽ�
	* ��ʼ��δʹ��DMA
	*��ѭ��ģʽ
	para1:32λ���ڲ����ݵ�ַ
	para2:32λ�Ĵ�����ַ
	para3:DMAͨ��
	para4:�����������λ65535
*/
void DMA_MP_Confg(uint32_t m_add,uint32_t p_add,DMA_Channel_TypeDef * CHANEL,uint16_t size)
{
	
	DMA_InitTypeDef DMA_InitStruct;
	//ʹ��     **DMA1**    ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//�����ڴ�������ַ
	DMA_InitStruct.DMA_PeripheralBaseAddr=p_add;
	DMA_InitStruct.DMA_MemoryBaseAddr=m_add;
	//ģʽ����λ���ڴ浽����
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralDST;
	//����������
	DMA_InitStruct.DMA_BufferSize=size;
	//�������������ģʽ���ڴ�λ����ģʽ
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	//�����ڴ��������ݴ�С
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	//��ѭ��ģʽ
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
	//�������ȼ�
	DMA_InitStruct.DMA_Priority=DMA_Priority_VeryHigh;
	//���ڴ浽�ڴ�ģʽ
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	//��ʼ��ͨ��
	DMA_Init(CHANEL,&DMA_InitStruct);
	//δʹ��
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
}



