#include     <stdio.h>		/*标准输入输出定义*/
#include     <stdlib.h>		/*标准函数库定义*/
#include     <unistd.h>		/*Unix 标准函数定义*/
#include     <string.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>		/*文件控制定义*/
#include     <termios.h>	/*PPSIX 终端控制定义*/
#include     <errno.h>		/*错误号定义*/


#define STTY_DEV "/dev/ttyUSB0"
#define BUFF_SIZE 256

int main()
{
  int stty_fd, n;
  u_int8_t buffer[BUFF_SIZE]={0};
  struct termios opt;

  /* 打开串口设备,可读可写 */
  stty_fd = open(STTY_DEV, O_RDWR|O_NOCTTY);
  if (-1==stty_fd) {
    perror("open device");
    return 0;
  }
  printf("Open device success, waiting user input ...\n");
  /* 取得当前串口配置，保存在termios结构体opt中 */
  tcgetattr(stty_fd, &opt);
//  刷清输入输出队列
  tcflush(stty_fd, TCIOFLUSH);

  /* 设置波特率 - 460800bps */
  cfsetispeed(&opt, B460800);
  cfsetospeed(&opt, B460800);

  /* 设置数据位 - 8位数据位 */
  opt.c_cflag &= ~CSIZE;
  opt.c_cflag |= CS8;

  ///////////////////////////////////////////////
  // 串口接收问题排查1
  //opt.c_oflag = ~ICANON;
  // 串口接收问题排查2
  //设置原始通信模式，串口不对接收到的数据进行处理而直接返回
	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	opt.c_oflag &= ~OPOST;
 	opt.c_iflag &= ~ (INLCR | ICRNL | IGNCR);
  opt.c_oflag &= ~(ONLCR | OCRNL);
  //opt.c_iflag &= ~(IXON | IXOFF | IXANY); //不要软件流控制
  opt.c_lflag |=(	CREAD |	CLOCAL);
  /////////////////////////////////////////////
  /* 设置奇偶位 - 无奇偶校验 */
  opt.c_cflag &= ~PARENB;
  opt.c_iflag &= ~INPCK;

  /* 设置停止位 - 1位停止位 */
  opt.c_cflag &= ~CSTOPB;

  /* 设置超时时间 - 15秒 */
  opt.c_cc[VTIME] = 0;
  opt.c_cc[VMIN] = 128;
  
  /* 设置写入设备参数，将opt信息不等传输完毕就写入*/
  if (0!=tcsetattr(stty_fd, TCSANOW, &opt)) {
    perror("set baudrate");
    return 0;
  }
  //  刷清输入输出队列
  tcflush(stty_fd, TCIOFLUSH);
  
  /* 读取数据，直到接收到'quit'字符串退出 */
  while(1) {
    //从stty_fd对应文件（此处为串口）读取数据至buffer，最大size个，返回读取量，到结束为读取到返回-1
    n = read(stty_fd,buffer,128);
    if (n<=0) {
      printf("read error");
      perror("read data");
      break;
    }
}
