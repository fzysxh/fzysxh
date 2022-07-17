#include<regx52.h>
#include"delay.h"
#include"MatrixKey.h"
#include"LCD1602.h"
#include"out.h"
void main()
{
	unsigned int num=0;
	unsigned int count,password;
	LCD_Init();
	LCD_ShowString(1,1,"HELLO WORLD");
	count=0;
	
	while(1)
	{
		  password=cs();
			if(password!=0)
			{
				if(password<=10);
				{
					if (count<4)
					{
						num*=10;
						num+=password%10;
						LCD_ShowNum(2,1,num,4);
						count++;
					}
				}
				if(password==12)
				{
				num=0;
				LCD_ShowNum(2,1,num,4);
				count=0;
				}
				if(password==11)
				{
					if(num==1012)
					{
						LCD_ShowString(1,14,"Hui");
						num=0;
						LCD_ShowNum(2,1,num,4);
						count=0;
					}
					else
					{
						LCD_ShowString(1,14,"ERR");
						num=0;
						LCD_ShowNum(2,1,num,4);
						count=0;
					}
					
				}
			}
			
		
		
	}
		
}