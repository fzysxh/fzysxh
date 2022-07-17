#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__
#include "stm32f10x.h"
#define I2C_SCL_PORT GPIOB
#define I2C_SDA_PORT GPIOB
#define I2C_SCL_CLK RCC_APB2Periph_GPIOB
#define I2C_SDA_CLK RCC_APB2Periph_GPIOB
#define I2C_SCL_Pin GPIO_Pin_6
#define I2C_SDA_Pin GPIO_Pin_7
#define I2C_SCL_1 GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_Pin)
#define I2C_SCL_0 GPIO_ResetBits(I2C_SCL_PORT,I2C_SCL_Pin )
#define I2C_SDA_1 GPIO_SetBits(I2C_SDA_PORT,I2C_SDA_Pin)
#define I2C_SDA_0 GPIO_ResetBits(I2C_SDA_PORT,I2C_SDA_Pin)
#define I2C_Get_SCL GPIO_ReadInputDataBit(I2C_SCL_PORT,I2C_SCL_Pin)
#define I2C_Get_SDA GPIO_ReadInputDataBit(I2C_SDA_PORT,I2C_SDA_Pin)
void I2c_Init(void);
void I2C_Star(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NAck(void);
u8 I2C_RA(void);
void I2C_WriteByte(u8 Data);
u8 I2C_RecieveByte(void);
#endif

