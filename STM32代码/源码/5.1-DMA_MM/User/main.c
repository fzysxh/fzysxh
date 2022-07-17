#include "stm32f10x.h"
#include "bsp_dma_mm.h"
#include "sys.h"
#include "bsp_led.h"
#include "delay.h"
int main(void)
{
	extern const uint32_t Flash_Const_Buffer[32];
	extern uint32_t SRAM_BUFFER[32];
	LED_Init();
	PEout(5)=1;
	DMA_MM_Confg();
	while(DMA_GetFlagStatus(DMA1_FLAG_TC6)==RESET);

	if(check(Flash_Const_Buffer,SRAM_BUFFER,32)==1)
	{
		PEout(5)=0;
	}
	else
	{
		PEout(5)=1;
	}
	while(1);
}




