#include "bsp_key.h"
#include "delay.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct_0;
	GPIO_InitTypeDef GPIO_InitStruct_1;
	GPIO_InitTypeDef GPIO_InitStruct_WK;
	GPIO_InitStruct_0.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct_1.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct_WK.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct_0.GPIO_Pin=KEY_0_GPIO_PIN;
	GPIO_InitStruct_1.GPIO_Pin=KEY_1_GPIO_PIN;
	GPIO_InitStruct_WK.GPIO_Pin=KEY_WK_GPIO_PIN;
	//使能KEY1，KEY0，KEY_WK_UP对应GPIO口时钟
	RCC_APB2PeriphClockCmd(KEY_0_CLK|KEY_1_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(KEY_WK_CLK, ENABLE);
	GPIO_Init(KEY_1_GPIO_PORT, &GPIO_InitStruct_1);
	GPIO_Init(KEY_0_GPIO_PORT, &GPIO_InitStruct_0);
	GPIO_Init(KEY_WK_GPIO_PORT,&GPIO_InitStruct_WK);
}
uint8_t KEY_Scan(uint8_t mode)
{	
	uint8_t key_0,key_1,key_wk;
	static uint8_t KEY=1;
	delay_init();
	key_0 = GPIO_ReadInputDataBit(KEY_0_GPIO_PORT,KEY_0_GPIO_PIN);
	key_1 = GPIO_ReadInputDataBit(KEY_1_GPIO_PORT,KEY_1_GPIO_PIN);
	key_wk = GPIO_ReadInputDataBit(KEY_WK_GPIO_PORT,KEY_WK_GPIO_PIN);
	if(mode==1){KEY=1;}
	if(KEY==1&&(key_0==0||key_1==0||key_wk==1))
	{
		delay_ms(15);
		KEY=0;
		if(key_0==0){return 0;}
		if(key_1==0){return 1;}
		if(key_wk==1){return 2;}
		
	}
	else if(key_0==1&&key_1==1&&key_wk==0)KEY=1;return 3;

}


