#include "logic.h"
extern int right;
extern int left;
#define high 30//75
#define med 20//50
#define low 0//25
void car_left()
{
	 right=high;
	 left=low;
}
void car_right()
{
	 right=low;
	 left=high;
}
void car_lleft()
{
	 right=med;
	 left=low;
}
void car_lright()
{
	 right=low;
	 left=med;
}
void car_stop()
{
	 right=0;
	 left=0;
}
void car_move()
{
	 right=med+8;
	 left=med;
}
void logic(unsigned char IN1,unsigned char IN2,unsigned char IN3,unsigned char IN4)
{
	//未检测到黑线，停止
	if(((IN1==1)&&(IN2==1)&&(IN3==1)&&(IN4==1)))
	{
		car_stop();
	}
	//黑线在中央，正常行驶
	if(((IN1==0)&&(IN2==1)&&(IN3==1)&&(IN4==0))||((IN1==0)&&(IN2==0)&&(IN3==0)&&(IN4==0)))
	{
		car_move();
	}
	//黑线偏左，车头偏右,左转
	if((IN1==0)&&(IN2==0)&&(IN3==1)&&(IN4==1))
	{
		car_lleft();
	}
	//黑线偏右，车头偏左,右转
	if((IN1==1)&&(IN2==1)&&(IN3==0)&&(IN4==0))
	{
		car_lright();
	}
	//右拐情况
	if((IN1==1)&&(IN2==0)&&(IN3==0)&&(IN4==0))
	{
		car_right();
	}
	//左拐情况
	if((IN1==0)&&(IN2==0)&&(IN3==0)&&(IN4==1))
	{
		car_left();
	}
	if((IN1==0)&&(IN2==0)&&(IN3==1)&&(IN4==0))
	{
		car_lleft();
	}
	if((IN1==0)&&(IN2==1)&&(IN3==0)&&(IN4==0))
	{
		car_lright();
	}
}
	