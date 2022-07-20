#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>  
#include <errno.h>

#define width 320
#define hight 240

int main(int argc ,const char *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if(sockfd<0)
	{
		printf("create sockfd error\r\n");	
	}
	printf("try--opening\r\n");					// 1.创建视频采集对象;
	VideoCapture cap;						// 2.打开默认相机;	
	cap.open(0);
	if (!cap.isOpened())
		return -1;
	printf("open success\r\n");					// 3.判断相机是否打开成功;
	cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));	//视频流格式					
	cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, hight);

 	//创建本机对象
	struct sockaddr_in addr;
   	addr.sin_family =AF_INET;
    addr.sin_port =htons(8888);
    addr.sin_addr.s_addr=inet_addr("192.168.43.58");
	socklen_t len=sizeof(addr);
	printf("ready to connect\r\n");
	if(connect(sockfd, (sockaddr*)&addr, sizeof(addr))<0)
	{
		printf("fail to connect\r\n");
		return 0;
	}
	
	printf("connected\r\n");
	unsigned char *data=new unsigned char[width*hight*3];

	while(1)
	{       
		Mat frame;
		cap >> frame; 
		memcpy(data,frame.data,width*hight*3);
		int rec;
		double start=getTickCount();
		int flag=300;
		sendto(sockfd,&flag,sizeof(flag),0,(struct sockaddr*)&addr,len);//发送帧头
				for(int i=0;i<hight;i++)
		{
		 	rec=sendto(sockfd,data+i*width*3,width*3,0,(struct sockaddr*)&addr,len);//一行一行的发送图像
		  
		}
		waitKey(50);
	}
}

