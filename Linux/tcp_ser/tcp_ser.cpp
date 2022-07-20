//头文件
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <sys/stat.h>
#include<arpa/inet.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define width 320
#define hight 240

int main(int argc, const char *argv[])
{
	int sockFd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockFd < 0)
	{
		puts("create socket error!");
		return -1;
	}
	 //创建本机对象
	struct sockaddr_in addr;
	addr.sin_family =AF_INET;
	addr.sin_port =htons(8888);
	addr.sin_addr.s_addr=inet_addr("192.168.164.131");//local ip
	int ret =bind(sockFd,(struct sockaddr*)&addr,sizeof(addr));//绑定本机端口
	if(ret<0)
	    {
		perror("bind\n");
		return -1;
	 
	    }
	//创建对象机
	int sClient = 0;
	struct sockaddr_in cli;//定义对象机的套接字
	socklen_t len=sizeof(cli);
	ret=listen(sockFd, 1);		//监听
	if(ret<0)
	{
		perror("listen error!");
	}
	sClient = accept(sockFd, (sockaddr*)&cli, &len); 
	unsigned char *data=new unsigned char[width*hight*3];
	namedWindow("im", 1);
	//resizeWindow("im", 640, 480);
	    while(1)
	    {
		 int buf;
		 recvfrom(sClient,&buf,sizeof(buf),0,(struct sockaddr*)&cli, &len);
		 if(buf==300)
		 {
			for(int i=0;i<hight;i=i+1)
			{
	
				int rec=recvfrom(sClient,data+i*width*3,width*3,0,(struct sockaddr*)&cli, &len);
			}            
			Mat im = Mat(hight,width,CV_8UC3,data);
			imshow("im",im);
			waitKey(50);
			//im.setTo(0);
			memset(data,0,width*hight*3);
			im.release();
	 
		 }
		         
	    }
	    close(sockFd);
}

