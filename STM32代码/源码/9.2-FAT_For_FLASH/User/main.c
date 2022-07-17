#include "stm32f10x.h"
#include "bsp_flash.h"
#include "bsp_spi.h"
#include "usart.h"
#include "delay.h"
#include "ff.h"
FATFS fsd;
FIL fp;
char Data[]="慧尝试回忆有关细节，而我意图 帮她走捷径";
char Rdata[500]="";
/*
  功能：此程序将FAT系统存放在FLASH的后8M空间内
  传入参数：
	1.
  返回：
*/
int main(void)
{
	FRESULT a;

	UINT  t, s;
	delay_init();
	uart_init(115200);
	FLASH_Init();
	//检查是否挂载FLASH
	a=f_mount(&fsd,"0:",1);
	if(a!=FR_OK)
	{
		//如果未挂载，进行挂载FLASH，选择立刻挂载
		f_mkfs("0:",0,0);
		//再次检查
		a=f_mount(&fsd,"0:",1);
	}
	//读取一个文件，设置为有就打开，没有就新建，基于写权限和读权限
	a=f_open(&fp,"0:abcd.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	if(a==FR_OK)
	{
		//如果打开成功，写入Data数组中数据，设置写入数目和一个写入量指针
		a=f_write(&fp,Data,sizeof(Data),&t);
		if(a==FR_OK)
		{
			//如果写入成功，打印写入量
			printf("t=%d\r",t);    
			//释放文件句柄，以便使用读取指令
			f_lseek(&fp,0);
			//读取刚才写入，存放与Rdata数组
			a=f_read(&fp,Rdata,f_size(&fp),&s);
			//打印读取量
			printf("s=%d\r",s);     
			//打印读取的数据
			printf("%s",Rdata);
		}

	}
	while(1)
	{

	}
}



