#include "bsp_tim_tpad.h"
#define FA 100
/*
	��ʼ����ʱ��5������ͨ��2������Ϊ�����ش���
	para1:TIM��Ƶϵ��
	para2:TIM���ֵ
*/
void TIM_CAPTURE_Init(u16 div,u16 cnt)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	//TIM5ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//��ʼ��TIM5������Ϊ����ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=cnt;
	TIM_TimeBaseInitStruct.TIM_Prescaler=div;
	//����Ϊͨ��2�����˲��������س�����ֱ��ӳ��
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0x00;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//��س�ʼ��������ʹ���ж�ָ��
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM5,ENABLE);
}
//���ݷŵ磬Ȼ���������IO��Ϊ�������룬�����ö�ʱ��Ϊ��
void TPAD_Reset()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	delay_ms(5);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	TIM_SetCounter(TIM5,0);
	
	
	
}
//��ȡһ�ε��ݳ����Ҫ��ʱ�䣬ԭ��Ϊ���һ��ֵ�󣬸�������ɲ���������
u16 TPAD_getval()
{
	u16 temp;
	TPAD_Reset();
	while(TIM_GetFlagStatus(TIM5,TIM_FLAG_CC2)==RESET);
	TIM_ClearFlag(TIM5,TIM_FLAG_CC2);
	temp=TIM_GetCapture2(TIM5);
	return temp;
}
//��ʼ�����ã��᷵�ص��ݳ����Ҫ��ʱ��
u16 TPAD_Init()
{
//����n��ɨ���г��ʱ�����һ��ʱ��
//para1��ɨ�����
//����n��ɨ���г��ʱ������һ��ʱ��
	//para1:ɨ�����
//����n�Σ������β���������ֵ
//para1: ��������
	u8 i,j;
	u32	temp1;
	u16 arr[10],temp;
	for(i=0;i<10;i++)
	{
		TPAD_Reset();
		arr[i]=TPAD_getval();
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<9-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	for(i=1;i<9;i++)
	{
		temp1+=arr[i];
	}
	temp1/=8;
	return temp1;
}
u16 TPAD_Max(u8 n)
{
//�������ڼ���Ƿ������ݰ�����������򷵻�1�����򷵻�0
//para1��ɨ��ģʽ��1֧��������0��֧������
//para2��ÿ��ɨ���ɨ�����
//para3��������������³��ʱ�������ڱȶԣ��ȶ�ֵΪx+FA���궨�壩
//�����⵽���°�������᷵��1�����򷵻�0
//para1��ģʽλ��1ʱ����������0ʱ������
//para2������ÿ��ɨ���ɨ�����
//para3��������������³��ʱ�䣬���ڱȶԣ��ȶ�ֵλx+FA���궨�壩
//�ж��Ƿ�ѹ���ݰ���
//para1:ģʽѡ��ѡ��1Ϊ֧��������2Ϊ��֧��
//para2������ÿ�βɼ���������
//para3��������������³�������Ҫ��ʱ�䣬���ڱȽ��Ƿ�����ָ��ѹ���Ƚ�ֵΪx+FA���궨�壩
	u8 i;
	u16 temp,res;
	for(i=0;i<n;i++)
	{
		temp=TPAD_getval();
		if(temp>res){res=temp;}
	}
	return res;
}
u8 logic(u8 mode,u8 times,u16 x)
{
	static u16 can=0;
	u8 res=0;
	if(mode==1){can=0;}
	if(TPAD_Max(times)>x+FA)
	{
		if(can==0)
		{
			res=1;
		}
		can=3;
	}
	if(can){can--;}
  return res;
}

