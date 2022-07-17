#include "stm32f10x.h"
#include "usart.h"
#include "bsp_spi.h"
#include "delay.h"
#include "sys.h"
int main(void)
{
	SPI2_Init();
	delay_init();
	uart_init(115200);
	printf("SPI≤‚ Ω≥Ã–Ú:");
	while(1)
	{
		//SPI_Test();    
		SPI_I2S_SendData(SPI2,0x32);
	}
}


