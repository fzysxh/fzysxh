#include "stm32f10x.h"
#include "bsp_led.h"
#include "sys.h"
#include "bsp_usart.h"
int main(void)
{
	uint8_t cher;
	unsigned char arrary[]={'a','d','g','i','a','n'};
	char Str[]="阿萨顶阿萨顶";
	My_USART_Init(115200);
	LED_Init();
/*	USART_NVIC_Init();

		串口接收中断如果初始化似乎会使后面串口点灯程序异常
	
*/
	
	USART1_SendByte(USART1,'d');
	USART1_SendHalfWord(USART1,'a');
	USART1_SendArrary(USART1,arrary,6);
	USART1_SendStr(USART1,Str);
	USART1_SendStr(USART1,"开启");
	while(1)
	{
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
		{
			cher=USART_ReceiveData(USART1);
			switch(cher)
			{
				case 1:PEout(5)=!PEout(5);break;
				case 2:PBout(5)=!PBout(5);break;
				case 3:USART1_SendStr(USART1,"滴滴aa！");break;
				default:USART1_SendStr(USART1,"滴滴！");PBout(5)=!PBout(5);break;
			}
		}
		
	}
}








