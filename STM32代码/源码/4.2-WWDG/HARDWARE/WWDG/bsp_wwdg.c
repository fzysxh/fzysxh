#include "bsp_wwdg.h"
uint8_t temp=0;
void WWDG_Init(uint8_t tr,uint8_t vr,uint32_t divid)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=WWDG_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	WWDG_SetPrescaler(divid);
	tr&=0x7f;
	temp=tr;
	vr&=0x7f;
	WWDG_Enable(tr);
	WWDG_SetWindowValue(vr);
	WWDG_ClearFlag();
	WWDG_EnableIT();
}
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(temp);
	WWDG_ClearFlag();
	PEout(5)=!PEout(5);
}


