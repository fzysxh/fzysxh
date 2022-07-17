#include"bsp_exti.h"

void EXIT_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	KEY_Init();
	//ʹ��EXIT�жϣ����ܸ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//�����жϲ���IO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	EXTI_InitStruct.EXTI_Line=EXTI_Line4;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	//��ʼ��
	EXTI_Init(&EXTI_InitStruct);
}
void NVIC_init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
}
void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)
	{
	PEout(5)=!PEout(5);
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}


