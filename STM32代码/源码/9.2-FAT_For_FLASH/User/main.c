#include "stm32f10x.h"
#include "bsp_flash.h"
#include "bsp_spi.h"
#include "usart.h"
#include "delay.h"
#include "ff.h"
FATFS fsd;
FIL fp;
char Data[]="�۳��Ի����й�ϸ�ڣ�������ͼ �����߽ݾ�";
char Rdata[500]="";
/*
  ���ܣ��˳���FATϵͳ�����FLASH�ĺ�8M�ռ���
  ���������
	1.
  ���أ�
*/
int main(void)
{
	FRESULT a;

	UINT  t, s;
	delay_init();
	uart_init(115200);
	FLASH_Init();
	//����Ƿ����FLASH
	a=f_mount(&fsd,"0:",1);
	if(a!=FR_OK)
	{
		//���δ���أ����й���FLASH��ѡ�����̹���
		f_mkfs("0:",0,0);
		//�ٴμ��
		a=f_mount(&fsd,"0:",1);
	}
	//��ȡһ���ļ�������Ϊ�оʹ򿪣�û�о��½�������дȨ�޺Ͷ�Ȩ��
	a=f_open(&fp,"0:abcd.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	if(a==FR_OK)
	{
		//����򿪳ɹ���д��Data���������ݣ�����д����Ŀ��һ��д����ָ��
		a=f_write(&fp,Data,sizeof(Data),&t);
		if(a==FR_OK)
		{
			//���д��ɹ�����ӡд����
			printf("t=%d\r",t);    
			//�ͷ��ļ�������Ա�ʹ�ö�ȡָ��
			f_lseek(&fp,0);
			//��ȡ�ղ�д�룬�����Rdata����
			a=f_read(&fp,Rdata,f_size(&fp),&s);
			//��ӡ��ȡ��
			printf("s=%d\r",s);     
			//��ӡ��ȡ������
			printf("%s",Rdata);
		}

	}
	while(1)
	{

	}
}



