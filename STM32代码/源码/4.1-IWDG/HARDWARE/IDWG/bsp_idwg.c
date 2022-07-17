#include "bsp_iwdg.h"
void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(0x09c4);//16分频下约一秒
	IWDG_Enable();
}

