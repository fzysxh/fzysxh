#include "stm32f10x.h"
#include "bsp_key.h"
#include "bsp_tim_capture.h"
#include "usart.h"
extern u8 STA;
extern u16 VAL;
u32 temp=0;
/*
	此程序通过定时器输入捕获，输出按下KEY_UP的时长
*/
int main(void)
{
	KEY_Init();
	uart_init(115200);
	TIM_CAPTURE_Init(71,0xFFFF);
	printf("我行");
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	while(1)
	{
		if(STA&0x80)
		{
			temp=(STA&0x3F);
			temp*=0xFFFF;
			temp+=VAL;
			printf("按下时长%d us",temp);
			STA=0;
		}
	}
}



