#include<regx52.h>
#include"LCD1602.h"
#include"DS1302.h"
#include"delay.h"
#include"independence_con.h"
#include"Timer0.h"
unsigned char n,m;
void LCD_Shine(unsigned char i)//指定位闪烁
{
			if(n==0 && m==1){LCD_ShowString(2,9,"  ");}
			else{LCD_ShowNum(2,9,DS1302_Data[0],2);}
			
			if(n==1 && m==1){LCD_ShowString(2,6,"  ");}
			else{LCD_ShowNum(2,6,DS1302_Data[1],2);}
	
				
			if(n==2 && m==1){LCD_ShowString(2,3,"  ");}
			else{LCD_ShowNum(2,3,DS1302_Data[2],2);}
				
				
			if(n==3 && m==1){LCD_ShowString(1,9,"  ");}
			else{LCD_ShowNum(1,9,DS1302_Data[3],2);}
				
				
			if(n==4 && m==1){LCD_ShowString(1,6,"  ");}
			else{LCD_ShowNum(1,6,DS1302_Data[4],2);}
					
				
			if(n== 5 && m==1){LCD_ShowString(2,1," ");}
			else{LCD_ShowNum(2,1,DS1302_Data[5],1);}
				
				
			if(n==6 && m==1){LCD_ShowString(1,3,"  ");}
			else{LCD_ShowNum(1,3,DS1302_Data[6],2);}
}
void LCD_Add()//指定位加一
{
	DS1302_Data[n]++;
	if(DS1302_Data[0]>59){DS1302_Data[0]=0;}
	if(DS1302_Data[1]>59){DS1302_Data[1]=0;}
	if(DS1302_Data[2]>24){DS1302_Data[2]=0;}
	//判断月份及大小年，确定日最大值
	if(DS1302_Data[4]==1 ||DS1302_Data[4]==3 ||DS1302_Data[4]==5 ||DS1302_Data[4]==7 ||DS1302_Data[4]==8 ||DS1302_Data[4]==10 ||DS1302_Data[4]==12)
	{
		if(DS1302_Data[3]>31){DS1302_Data[3]=0;}
	}
	else
	{
		if(DS1302_Data[4]==2)
		{
			if(DS1302_Data[6]%4 || DS1302_Data[6]%100){DS1302_Data[3]%=29;}
			else{DS1302_Data[3]%=30;}
		}
		else{DS1302_Data[3]%=31;}
	}	
	DS1302_Data[4]%=13;
	DS1302_Data[5]%=8;
	DS1302_Data[6]%=101;
	DS1302_Set();
}
void LCD_Deadd()//指定位减一
{
	DS1302_Data[n]--;
	if(DS1302_Data[0]<0){DS1302_Data[0]=59;}
	if(DS1302_Data[1]<0){DS1302_Data[1]=59;}
	if(DS1302_Data[2]<0){DS1302_Data[2]=24;}
	if(DS1302_Data[4]==1 ||DS1302_Data[4]==3 ||DS1302_Data[4]==5 ||DS1302_Data[4]==7 ||DS1302_Data[4]==8 ||DS1302_Data[4]==10 ||DS1302_Data[4]==12)
	{
		if(DS1302_Data[3]<0){DS1302_Data[3]=31;}
	}
	else
	{
		if(DS1302_Data[4]==2)
		{
			if(DS1302_Data[6]%4 || !DS1302_Data[6]%100){if(DS1302_Data[3]<0){DS1302_Data[3]=28;}}
			else{if(DS1302_Data[3]<0){DS1302_Data[3]=29;}}
		}
		else{if(DS1302_Data[3]<0){DS1302_Data[3]=30;}}
	}	
	if(DS1302_Data[4]<0){DS1302_Data[4]=12;}
	if(DS1302_Data[5]<0){DS1302_Data[5]=7;}
	if(DS1302_Data[6]<0){DS1302_Data[6]=99;}
}
void main()
{
	char KEY;
	Timer0Init();
	DS1302_Init();
	LCD_Init();
  DS1302_Set();
	LCD_ShowString(1,1,"    -  -");
	LCD_ShowString(2,1," -  :  :");
	while(1)
	{
		DS1302_Get();
		LCD_ShowNum(1,1,20,2);
		LCD_ShowNum(1,3,DS1302_Data[6],2);
		LCD_ShowNum(1,6,DS1302_Data[4],2);
		LCD_ShowNum(1,9,DS1302_Data[3],2);
		LCD_ShowNum(2,1,DS1302_Data[5],1);
		LCD_ShowNum(2,3,DS1302_Data[2],2);
		LCD_ShowNum(2,6,DS1302_Data[1],2);
	  LCD_ShowNum(2,9,DS1302_Data[0],2);
		KEY = independent();
		if(KEY==1)
		{
			n=0;
			KEY = 0;
			while(KEY!=1)
			{
				LCD_Shine(n);
				KEY = independent();
				if(KEY==2)
				{
					n++;
    			if(n>=7){n=0;}
			  }	
				if(KEY==3)
				{LCD_Add();}
				if(KEY==4)
				{LCD_Deadd();}
			}
		}
	}
}
void Timer0(void)		interrupt 1//用于闪烁
{
	static unsigned int count;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	count++;
	if(count>=500)
	{
		count=0;
		m=!m;
	}
} 