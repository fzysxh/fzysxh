#include "stm32f10x.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_buzzer.h"
#include "sys.h"
#include "delay.h"
int main(void)
{
	uint8_t conmand,temp=0;
	KEY_Init();
	LED_Init();
	delay_init();
	BUZZER_Init();
	PEout(5)=0;
	PBout(5)=0;
	while(1)
	{
		conmand=KEY_Scan(0);
		if(conmand==0)
		{
			if(temp==0){PEout(5)=!PEout(5);}
			else if(temp==1){PBout(5)=!PBout(5);}
			temp++;
			temp%=2;
		}
		if(conmand==1)
		{
			PEout(5)=!PEout(5);
			PBout(5)=!PBout(5);
		}
		if(conmand==2)
		{
			PBout(8)=!PBout(8);
		}
	}
}






