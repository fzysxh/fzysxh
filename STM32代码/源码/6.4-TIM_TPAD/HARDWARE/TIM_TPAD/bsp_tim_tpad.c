#include "bsp_tim_tpad.h"
#define FA 100
/*
	初始化定时器5，捕获通道2，设置为上升沿触发
	para1:TIM分频系数
	para2:TIM溢出值
*/
void TIM_CAPTURE_Init(u16 div,u16 cnt)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	//TIM5时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//初始化TIM5，设置为向上模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=cnt;
	TIM_TimeBaseInitStruct.TIM_Prescaler=div;
	//设置为通道2，无滤波，上升沿出发，直接映射
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0x00;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	//相关初始化函数，使能中断指令
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM5,ENABLE);
}
//电容放电，然后设置相关IO口为浮空输入，并设置定时器为零
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
//获取一次电容充电需要的时间，原理为充电一定值后，浮空输入可捕获到上升沿
u16 TPAD_getval()
{
	u16 temp;
	TPAD_Reset();
	while(TIM_GetFlagStatus(TIM5,TIM_FLAG_CC2)==RESET);
	TIM_ClearFlag(TIM5,TIM_FLAG_CC2);
	temp=TIM_GetCapture2(TIM5);
	return temp;
}
//初始化设置，会返回电容充电需要的时间
u16 TPAD_Init()
{
//返回n次扫描中充电时长最长的一次时长
//para1：扫描次数
//返回n次扫描中充电时长最大的一次时长
	//para1:扫描次数
//采样n次，输出多次采样中最大的值
//para1: 采样次数
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
//程序用于检测是否触摸电容按键，如果有则返回1，否则返回0
//para1：扫描模式，1支持连按，0不支持连按
//para2：每次扫描的扫描次数
//para3：电容正常情况下充电时长，用于比对，比对值为x+FA（宏定义）
//如果检测到按下按键，则会返回1，否则返回0
//para1：模式位，1时允许连按，0时不允许
//para2：设置每个扫描的扫描次数
//para3：传入正常情况下充电时间，用于比对，比对值位x+FA（宏定义）
//判断是否按压电容按键
//para1:模式选择，选择1为支持连按，2为不支持
//para2：设置每次采集采样次数
//para3：电容正常情况下冲满电需要的时间，用于比较是否有手指按压，比较值为x+FA（宏定义）
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

