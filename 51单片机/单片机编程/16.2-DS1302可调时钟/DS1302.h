#ifndef __DS1302_H__
#define __DS1302_H__
void DS1302_Init();
unsigned char DS1302_Read(unsigned char command);
void DS1302_Write(unsigned char command,Data);
extern char DS1302_Data[];
void DS1302_Get();
void DS1302_Set();
#endif