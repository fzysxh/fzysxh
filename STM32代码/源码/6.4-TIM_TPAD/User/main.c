#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_tim_tpad.h"
#include "sys.h"
//��������֮�����ȡ���ݳ��ʱ�䣬��λ�����ʱ����
//�������ݰ������ܻᵼ�³����쳣
int main(void)
{
	u16 temp;
	TIM_CAPTURE_Init(71,0xFFFF);
	delay_init();
	temp=TPAD_Init();
	LED_Init();
	while(1)
	{
		if(logic(0,temp,3)==1)
		{
			PEout(5)=!PEout(5);
		}
	}
}



