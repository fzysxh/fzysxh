/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */


/* Definitions of physical drive number for each drive */
#define SPI_FLASH 0
#define CD_CARD 1

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case SPI_FLASH :
		result = FLASH_Read_ID();
		if(result==0x522118)
		{stat=RES_OK;}
		else{stat=RES_ERROR;}
		return stat;

	case CD_CARD :  



		return stat;
}

	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case SPI_FLASH :
		 FLASH_Init();
		stat=RES_OK;

		return stat;

	case CD_CARD :
//		result = MMC_disk_initialize();


		return stat;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv) {
	case SPI_FLASH :
		sector+=2048;
		FLASH_Read_Arr(sector*4096,buff,count*4096);
		res=RES_OK;
		return res;

	case CD_CARD :


		return res;


	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	switch (pdrv) {
	case SPI_FLASH :
		sector+=2048;
		FLASH_Write_Check(sector*4096,(u8 *)buff,count*4096);
		res=RES_OK;
		return res;
	case CD_CARD :
		// translate the arguments here

//		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	switch (pdrv) {
	case SPI_FLASH :
		switch(cmd)
		{
			case GET_SECTOR_COUNT:
				*(DWORD *)buff=2048;
				break;
			case GET_SECTOR_SIZE:
				*(WORD *)buff=4096;
				break;
			case GET_BLOCK_SIZE:
				//同时擦除扇区个数
				*(WORD *)buff=1;
				break;
		}
		res=RES_OK;
		return res;

	case CD_CARD :


		return res;

	}

	return RES_PARERR;
}
#endif
