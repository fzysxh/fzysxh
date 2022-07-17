#include "stm32f10x.h"
#include "bsp_flash.h"
#include "bsp_spi.h"
#include "usart.h"
#include "delay.h"
#define HSB 0xA1
#define LSB 0xE5
 u8 Arr[32]={0};
 u16 i;
 void ea();
 void re();
int main(void)
{
	
	delay_init();
	uart_init(115200);
	FLASH_Init();
	FLASH_Wait_Busy();  
ea();
re(0x37fe0);

	while(1)
	{

	}
}
void ea()
{
	for(i=0;i<16*128;i++)
	{
		
		if(i==55)
		{
			i=i;
		}
		
if(i==56)
{i=i;}
		FLASH_ERASE_SECTOR(i*4096+20);
	}
	printf("Ok");
}
void re(u32 adr)
{
	FLASH_Read_Arr(adr,Arr,32);
	FLASH_Wait_Busy();
	for(i=0;i<32;i++)
	{
		printf("%d  ",Arr[i]);
	}
}


