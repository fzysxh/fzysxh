#ifndef __I2C_H__
#define __I2C_H__
void I2C_Start();
void I2C_Stop();
void I2C_WriteByte(unsigned char Byte);
unsigned char I2C_ReceiveByte();
void I2C_SA(unsigned char Byte);
unsigned char I2C_RA();
#endif