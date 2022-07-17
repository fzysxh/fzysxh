#include "bsp_tim_pwm.h"
/*
	* 初始化定时器3及其中断
	* 设定为递增模式
	para1:分频系数最大为65536
	para2:溢出值，最大为65536
*/
void TIM_PWM_Init(u16 div,u16 cnt)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

//设置为cnt大于预设值有效，极性为高
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;

	//不知道是干嘛的
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	//设置重装载值
	TIM_TimeBaseInitStruct.TIM_Period=cnt;
	//分频设定
	TIM_TimeBaseInitStruct.TIM_Prescaler=div;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//设置为输出比较模式
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);
}

