#include<regx52.h>
void delay(unsigned char i)
{
	while(i--);
}
void main()
{
	unsigned char Time,t;
	while(1)
	{
  	for(Time=0;Time<100;Time++)
 	 {
	  	for(t=0;t<30;t++)
		 {
		 P2_0=0;
		 delay(Time);
		 P2_0=1;
		 delay(100-Time);
		 }
	 }
	 for(Time=100;Time>0;Time--)
	 {
		 for(t=0;t<30;t++)
		 {
		 P2_0=0;
		 delay(Time);
		 P2_0=1;
		 delay(100-Time);
		 }
	 }
	}
	
}