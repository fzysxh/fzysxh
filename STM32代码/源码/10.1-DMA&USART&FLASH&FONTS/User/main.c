#include "stm32f10x.h"
#include "bsp_dma_mp.h"
//#include "bsp_usart.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "bsp_spi.h"
#include "bsp_flash.h"
u8 part=0,de=0;
u32 Adr=0;
uint8_t arr[8192]={0};
int main()
{
	delay_init();
	FLASH_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//My_USART_Init();
	uart_init(115200);
	DMA_MP_Confg((uint32_t) arr,(USART1_BASE+0x04),DMA1_Channel5,8192);
	USART_DMACmd(USART1,USART_DMAReq_Rx|USART_DMAReq_Rx,ENABLE);

	while(1)
	{
		if(de==1)
		{
			switch(part)
			{
				case 0:
				{
					FLASH_Write_NoCheck(Adr,arr,4096);
					de=0;Adr+=4096;break;
				}
				case 1:
				{
					FLASH_Write_NoCheck(Adr,arr+4096,4096);
					de=0;Adr+=4096;break;
				}
			}			
		}
	}
}

void DMA1_Channel5_IRQHandler()
{
	//半满中断
	if(DMA_GetITStatus(DMA1_IT_HT5)==SET)
	{
		part=0;de=1;
		DMA_ClearITPendingBit(DMA1_IT_HT5);
	}
	//完成中断
	if(DMA_GetITStatus(DMA1_IT_TC5)==SET)
	{
		part=1;de=1;
		DMA_ClearITPendingBit(DMA1_IT_TC5);
	}
}

