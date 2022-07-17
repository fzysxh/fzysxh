#include "stm32f10x.h"
#include "bsp_i2c.h"
#include "bsp_e2prom.h"
#include "bsp_oled.h"
#include "delay.h"
/*�˳���Ϊͨ��I2C��E2PROMͨѶ��д�����ݲ���ȡ��ͨ��OLED��ʾ*/
int main(void)
{
	u8 Arr[10]={0};
	delay_init();
	I2c_Init();
	OLDE_Init(); 
	OLED_Clear();
	E2PROM_WriteStr(1,"fzy");
	E2PROM_ReadStr(1,3,Arr);
	OLED_ShowStr_EN(0,0,Arr);
	while(1)
	{
		
	}
	
}



