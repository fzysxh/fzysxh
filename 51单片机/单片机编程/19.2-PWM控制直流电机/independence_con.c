#include<regx52.h>
#include"delay.h"
/*
    brief:检测按键并输出键码值
    come_in:无
    out:键码值
*/
char independent()
{
	unsigned int KEY=0;
	if(P3_1==0){delay(20);while(P3_1==0);KEY=1;}
	if(P3_0==0){delay(20);while(P3_0==0);KEY=2;}
	if(P3_2==0){delay(20);while(P3_2==0);KEY=3;}
	if(P3_3==0){delay(20);while(P3_3==0);KEY=4;}
	return KEY;
}