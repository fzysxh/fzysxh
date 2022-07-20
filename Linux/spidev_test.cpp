#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

static const char *device = "/dev/spidev0.1";
static uint8_t mode=0;							//模式0,SCLK空闲为低，第一个沿采样
static uint8_t bits = 8;						//八位传输
static uint32_t speed = 500000;				//设置频率，500kHz
static uint16_t delay;							//两个transfer之间时差
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static void transfer(int fd);
int main(int argc, char *argv[])
{
	int ret = 0;
	int fd;


	fd = open(device, O_RDWR);	//可读可写打开设备
	if (fd < 0)			//打开失败打印信息
		printf("can't open device");

	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);			//配置SPI模式
	if (ret == -1)
		printf("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		printf("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);	//设置数据长度
	if (ret == -1)
		printf("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);	//设置最大传输速度
	if (ret == -1)
		printf("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't get max speed hz");

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);	
	transfer(fd);
	close(fd);
	return ret;
}
static void transfer(int fd)
{
	int ret;
	uint8_t tx[] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
		0xF0, 0x0D,
	};
	//定义接收数组
	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,  	//发送缓冲
		.rx_buf = (unsigned long)rx,	//接收缓冲
		.len = ARRAY_SIZE(tx),		//每次将tx数组尽数发送
		.speed_hz = speed,		//定义传输的时钟频率
		.delay_usecs = delay,           //两个transfer之间延时
		.bits_per_word = bits,		//定义每次传输的字长
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		printf("can't send spi message");

	for (ret = 0; ret < ARRAY_SIZE(tx); ret++) {
		if (!(ret % 6))
			puts("");
		printf("%.2X ", rx[ret]);
	}
	puts("");
}
