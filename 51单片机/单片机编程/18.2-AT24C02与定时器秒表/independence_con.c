#include<regx52.h>
#include"delay.h"
unsigned char KEY1;
/*
    brief:检测按键并输出键码值
    come_in:无
    out:键码值
*/
char independent()
{
	unsigned int KEY=0;
	if(P3_1==0){KEY=1;}
	if(P3_0==0){KEY=2;}
	if(P3_2==0){KEY=3;}
	if(P3_3==0){KEY=4;}
	return KEY;
}

char KEY_Loop()
{
	static unsigned char now,last;
	last=now;
	now=independent();
	if(last==1 & now==0){KEY1=1;}
	if(last==2 & now==0){KEY1=2;}
	if(last==3 & now==0){KEY1=3;}
	if(last==4 & now==0){KEY1=4;}
	return KEY1;
}
unsigned char Key(void)
{
	unsigned char Temp=0;
	Temp=KEY1;
	KEY1=0;
	return Temp;
}