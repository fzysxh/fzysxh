#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__
#include "stm32f10x.h"
#include "bsp_spi.h"
#include "delay.h"

#define FLASH_High GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define FLASH_Low GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define PageSize 256
#define SectorSize 4096

#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void FLASH_Init(void);
void FLASH_PowerDown(void);
void FLASH_Relase(void);
u32 FLASH_Read_ID(void);
void FLASH_Write_ENABLE(void);
void FLASH_Write_DISABLE(void);
void FLASH_Wait_Busy(void);
void FLASH_ERASE_SECTOR(u32 Adr);
void FLASH_ERASE_BLOCK(u32 Adr);
void FLASH_ERASE_ALL(void);
u8 FLASH_ReadByte(u32 Adr);
void FLASH_Read_Arr(u32 Adr,u8 * Arr,u16 len);
void FLASH_WriteByte(u32 Adr,u8 Data);
void FLASH_WritePage_NoCheck(u32 Adr,u8 *Arr,u16 len);
void FLASH_Write_NoCheck(u32 Adr,u8 *Arr,u16 len);
void FLASH_Write_Check(u32 Adr,u8 *Arr,u16 len);

#endif

