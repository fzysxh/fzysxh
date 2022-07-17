#include "stm32f10x.h"
#include "bsp_buzzer.h"
#include "delay.h"
#include "sys.h"
int main(void)
{
	BUZZER_Init();
	delay_init();
	while(1)
	{
		PBout(8)=0;
		delay_ms(300);	
		PBout(8)=1;
		delay_ms(300);
	}
	
}



