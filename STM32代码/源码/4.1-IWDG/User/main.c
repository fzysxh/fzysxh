#include "stm32f10x.h"
#include "sys.h"
#include "bsp_iwdg.h"
#include "bsp_led.h"
#include "bsp_buzzer.h"
#include "bsp_key.h"
int main(void)
{
	LED_Init();
	KEY_Init();
	BUZZER_Init();
	IWDG_Init();
	PEout(5)==0;
	while(1)
	{
		if(KEY_Scan(0)==0)
		{
			PEout(5)=!PEout(5);
		}
		if(PEout(5)==0)
		{
			IWDG_ReloadCounter();
		}
	}
}



