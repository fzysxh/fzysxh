#include "bsp_tim_ir.h"
void TIM_Ir_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	
	//��֪���Ǹ����
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//������װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Period=4999;
	//��Ƶ�趨Ϊ7200
	TIM_TimeBaseInitStruct.TIM_Prescaler=7199;
	/*��ʱ��ʱ��ÿ5000*7200/72M=0.5����װ��һ��*/
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	NVIC_Init(&NVIC_InitStruct);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}
void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		PEout(5)=!PEout(5);
	}
}

