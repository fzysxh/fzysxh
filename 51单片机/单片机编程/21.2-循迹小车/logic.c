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
	//δ��⵽���ߣ�ֹͣ
	if(((IN1==1)&&(IN2==1)&&(IN3==1)&&(IN4==1)))
	{
		car_stop();
	}
	//���������룬������ʻ
	if(((IN1==0)&&(IN2==1)&&(IN3==1)&&(IN4==0))||((IN1==0)&&(IN2==0)&&(IN3==0)&&(IN4==0)))
	{
		car_move();
	}
	//����ƫ�󣬳�ͷƫ��,��ת
	if((IN1==0)&&(IN2==0)&&(IN3==1)&&(IN4==1))
	{
		car_lleft();
	}
	//����ƫ�ң���ͷƫ��,��ת
	if((IN1==1)&&(IN2==1)&&(IN3==0)&&(IN4==0))
	{
		car_lright();
	}
	//�ҹ����
	if((IN1==1)&&(IN2==0)&&(IN3==0)&&(IN4==0))
	{
		car_right();
	}
	//������
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
	