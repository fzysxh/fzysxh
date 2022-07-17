#include "bsp_tim_pwm.h"
/*
	* ��ʼ����ʱ��3�����ж�
	* �趨Ϊ����ģʽ
	para1:��Ƶϵ�����Ϊ65536
	para2:���ֵ�����Ϊ65536
*/
void TIM_PWM_Init(u16 div,u16 cnt)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

//����Ϊcnt����Ԥ��ֵ��Ч������Ϊ��
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;

	//��֪���Ǹ����
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//������װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Period=cnt;
	//��Ƶ�趨
	TIM_TimeBaseInitStruct.TIM_Prescaler=div;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//����Ϊ����Ƚ�ģʽ
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);
}

