#include "bsp_tim_capture.h"
u8 STA=0;//最高位为是否捕获完成，第七位为是否捕获过上升沿，其余为计时器溢出次数
u16 VAL=0;//用于记录捕获完成时，输入捕获寄存器内值
/*
	函数初始化了TIM5，及其输入捕获和更新中断，输入捕获中断
	para1:TIM分频系数
	para2:TIM溢出值
*/
void TIM_CAPTURE_Init(u16 div,u16 cnt)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	//TIM5时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	//初始化NVIC
	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	//初始化TIM5，设置为向上模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=cnt;
	TIM_TimeBaseInitStruct.TIM_Prescaler=div;
	//初始化输入捕获，不滤波，映射至通道一
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0x00;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//相关初始化函数，使能中断指令
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
		if(STA&0x40)										//计时器更新，如果已进入高电平（即捕获过上升沿）
		{
			STA++;												//溢出次数加1
			if((STA&0x3F)==0x3F)					//最高记录0x3F次溢出，如果达到最高，
			{															//就强制结束，设置为捕获完成
				STA|=0x80;
			}
		}
	}
	if(TIM_GetITStatus(TIM5,TIM_IT_CC1)!=RESET)
	{
		
		if(STA&0x40)										//捕获中断，如果之前捕获过上升沿（捕获后下次捕获下降沿），则此次捕获为下降
		{																//设置完成捕获，记录捕获寄存器当前值，重新设置下次捕获上升沿
			STA|=0x80;
			VAL=TIM_GetCapture1(TIM5);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
		}
		else
		{																//如果未捕获过上升沿，则开始记录高电平时间，初始化STA，VAL
			STA=0;												//设置为下次捕获下降沿，已捕获上升沿
			VAL=0;
			STA|=0x40;
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update);
}

