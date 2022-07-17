#include "stm32f10x.h"
#include "bsp_key.h"
#include "bsp_tim_capture.h"
#include "usart.h"
extern u8 STA;
extern u16 VAL;
u32 temp=0;
/*
	�˳���ͨ����ʱ�����벶���������KEY_UP��ʱ��
*/
int main(void)
{
	KEY_Init();
	uart_init(115200);
	TIM_CAPTURE_Init(71,0xFFFF);
	printf("����");
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	while(1)
	{
		if(STA&0x80)
		{
			temp=(STA&0x3F);
			temp*=0xFFFF;
			temp+=VAL;
			printf("����ʱ��%d us",temp);
			STA=0;
		}
	}
}



