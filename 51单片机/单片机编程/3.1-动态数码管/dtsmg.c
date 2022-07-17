#include<regx52.h>
#include<intrins.h>
#include"delay.h"
#include"smgnumber.h"
typedef unsigned int u16;
typedef unsigned char u8;

void main()
{	
	while(1)
	{
		smgnumber(1,2);//第几位，显示数字
		smgnumber(2,0);
		smgnumber(3,0);
		smgnumber(4,2);
		smgnumber(5,1);
		smgnumber(6,0);
		smgnumber(7,1);
		smgnumber(8,5);
	}
	
}