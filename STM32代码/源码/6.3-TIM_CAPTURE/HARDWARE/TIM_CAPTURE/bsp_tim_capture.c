#include "bsp_tim_capture.h"
u8 STA=0;//���λΪ�Ƿ񲶻���ɣ�����λΪ�Ƿ񲶻�������أ�����Ϊ��ʱ���������
u16 VAL=0;//���ڼ�¼�������ʱ�����벶��Ĵ�����ֵ
/*
	������ʼ����TIM5���������벶��͸����жϣ����벶���ж�
	para1:TIM��Ƶϵ��
	para2:TIM���ֵ
*/
void TIM_CAPTURE_Init(u16 div,u16 cnt)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	//TIM5ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	//��ʼ��NVIC
	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	//��ʼ��TIM5������Ϊ����ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=cnt;
	TIM_TimeBaseInitStruct.TIM_Prescaler=div;
	//��ʼ�����벶�񣬲��˲���ӳ����ͨ��һ
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0x00;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//��س�ʼ��������ʹ���ж�ָ��
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	NVIC_Init(&NVIC_InitStruct);
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_Cmd(TIM5,ENABLE);
}

void TIM5_IRQHandler()
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
	{
		if(STA&0x40)										//��ʱ�����£�����ѽ���ߵ�ƽ��������������أ�
		{
			STA++;												//���������1
			if((STA&0x3F)==0x3F)					//��߼�¼0x3F�����������ﵽ��ߣ�
			{															//��ǿ�ƽ���������Ϊ�������
				STA|=0x80;
			}
		}
	}
	if(TIM_GetITStatus(TIM5,TIM_IT_CC1)!=RESET)
	{
		
		if(STA&0x40)										//�����жϣ����֮ǰ����������أ�������´β����½��أ�����˴β���Ϊ�½�
		{																//������ɲ��񣬼�¼����Ĵ�����ǰֵ�����������´β���������
			STA|=0x80;
			VAL=TIM_GetCapture1(TIM5);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
		}
		else
		{																//���δ����������أ���ʼ��¼�ߵ�ƽʱ�䣬��ʼ��STA��VAL
			STA=0;												//����Ϊ�´β����½��أ��Ѳ���������
			VAL=0;
			STA|=0x40;
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update);
}

