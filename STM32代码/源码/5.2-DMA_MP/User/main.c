#include "stm32f10x.h"
#include "bsp_dma_mp.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
/*此程序有问题，不加while（1）向串口发送
  的是有规律的乱码，最后加上点延时也能避免，好像
	程序在没有while（1）；的情况下也会循环，因为在
	加上设定发送数据数为5000的语句，就会一直发送，
	而且如果是分别写LED灭，LED明，LED的亮度会保持
	在微弱的状态，还不知道啥情况.
*/
/*经过查找资料，初步定位问题应该是整个程序不加while
  之类main函数会退出，而在关闭半主机的情况下，程序会
	在结束后重新回到开始的地方，不知与复位的关系如何
*/
/*关于这个程序巨离谱的是，我2.8晚上调试还发送乱码，2.9
  早上该都没改，它突然就可以了，欸，嗯。
*/
//由于数组的长度限制，将数组放在主函数里做局部变量在1700左右大小
//导致奇怪的问题（数据量超过1700多少后，串口收不到一个数据）
//有趣的问题
uint8_t arr[5000];
int main()
{
	uint16_t i=0;
	
	uart_init(115200);
	for(i=0;i<5000;i++)
	{
	arr[i]= 'P';
	}
	DMA_MP_Confg((uint32_t) arr,(USART1_BASE+0x04),DMA1_Channel4,5000);

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	while(1);
}



