/*
	板级支持包--正点原子精英板
  控制ili8552驱动LCD，使用的初始化指令是7789的
	使用FSMC模拟8080时序
	颜色为RGB565
*/
#include "bsp_lcd_ili9341.h"
u16 XSide=ShortSide;
u16 YSide=LongSide;
u8 grammode=6;
Font_Table *CurFont=&Font_8x16;
//定义了起始点，通过它可以调节字符串显示换行后的位置（需要开启换行操作）
#define X_Star 0
#define Y_Star 0
void FSMC_Config(void)
{
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;
	FSMC_NORSRAMTimingInitTypeDef ReadTimingStruct;
	FSMC_NORSRAMTimingInitTypeDef WriteTimingStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	
	ReadTimingStruct.FSMC_AccessMode=FSMC_AccessMode_A;
	ReadTimingStruct.FSMC_AddressHoldTime=0x00;
	ReadTimingStruct.FSMC_AddressSetupTime=0x01;
	ReadTimingStruct.FSMC_BusTurnAroundDuration=0x00;
	ReadTimingStruct.FSMC_CLKDivision=0x00;
	ReadTimingStruct.FSMC_DataLatency=0x00;
	ReadTimingStruct.FSMC_DataSetupTime=0x0f;
	
	WriteTimingStruct.FSMC_AccessMode=FSMC_AccessMode_A;
	WriteTimingStruct.FSMC_AddressHoldTime=0x00;
	WriteTimingStruct.FSMC_AddressSetupTime=0x00;
	WriteTimingStruct.FSMC_BusTurnAroundDuration=0x00;
	WriteTimingStruct.FSMC_CLKDivision=0x00;
	WriteTimingStruct.FSMC_DataLatency=0x00;
	WriteTimingStruct.FSMC_DataSetupTime=0x03;
	
	FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStruct.FSMC_Bank=FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode=FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStruct.FSMC_DataAddressMux=FSMC_DataAddressMux_Disable;;
	FSMC_NORSRAMInitStruct.FSMC_ExtendedMode=FSMC_ExtendedMode_Enable;
	FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth=FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStruct.FSMC_MemoryType=FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct=&ReadTimingStruct;
	FSMC_NORSRAMInitStruct.FSMC_WaitSignal=FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive=FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity=FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStruct.FSMC_WrapMode=FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStruct.FSMC_WriteBurst=FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStruct.FSMC_WriteOperation=FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct=&WriteTimingStruct;
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
	FSMC_NORSRAMCmd ( FSMC_Bank1_NORSRAM4, ENABLE );
	delay_ms(50);
}
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_APB2PeriphClockCmd ( 	
													ILI9341_CS_CLK|ILI9341_RS_CLK|ILI9341_WR_CLK|
													ILI9341_RD_CLK	|ILI9341_BL_CLK|
													ILI9341_DB1_CLK | ILI9341_DB2_CLK | ILI9341_DB3_CLK| 
													ILI9341_DB4_CLK | ILI9341_DB5_CLK | ILI9341_DB6_CLK|
													ILI9341_DB7_CLK | ILI9341_DB8_CLK | ILI9341_DB10_CLK|
													ILI9341_DB11_CLK | ILI9341_DB12_CLK | ILI9341_DB13_CLK|
													ILI9341_DB14_CLK | ILI9341_DB15_CLK | ILI9341_DB16_CLK|
													ILI9341_DB17_CLK	, ENABLE );
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_CS_Pin;
	GPIO_Init(ILI9341_CS_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_RD_Pin; 
	GPIO_Init(ILI9341_RD_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_WR_Pin; 
	GPIO_Init(ILI9341_WR_PORT,&GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_RS_Pin; 
	GPIO_Init(ILI9341_RS_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB1_Pin;
	GPIO_Init ( ILI9341_DB1_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB2_Pin;
	GPIO_Init ( ILI9341_DB2_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB3_Pin;
	GPIO_Init ( ILI9341_DB3_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB4_Pin;
	GPIO_Init ( ILI9341_DB4_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB5_Pin;
	GPIO_Init ( ILI9341_DB5_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB6_Pin;
	GPIO_Init ( ILI9341_DB6_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB7_Pin;
	GPIO_Init ( ILI9341_DB7_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB8_Pin;
	GPIO_Init ( ILI9341_DB8_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB10_Pin;
	GPIO_Init ( ILI9341_DB10_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB11_Pin;
	GPIO_Init ( ILI9341_DB11_PORT, & GPIO_InitStruct );

	GPIO_InitStruct.GPIO_Pin = ILI9341_DB12_Pin;
	GPIO_Init ( ILI9341_DB12_PORT, & GPIO_InitStruct );	
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB13_Pin;
	GPIO_Init ( ILI9341_DB13_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB14_Pin;
	GPIO_Init ( ILI9341_DB14_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB15_Pin;
	GPIO_Init ( ILI9341_DB15_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB16_Pin;
	GPIO_Init ( ILI9341_DB17_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Pin = ILI9341_DB17_Pin;
	GPIO_Init ( ILI9341_DB17_PORT, & GPIO_InitStruct );
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = ILI9341_BL_Pin; 
	GPIO_Init ( ILI9341_BL_PORT, & GPIO_InitStruct );
}	
void LCD_Config()
{
	LCD_WriteCmd(0x11);
	delay_ms(120);

	LCD_WriteCmd(0x36);
	LCD_WriteData(0x00);


	LCD_WriteCmd(0x3A);
	LCD_WriteData(0X05);

	LCD_WriteCmd(0xB2);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x00);
	LCD_WriteData(0x33);
	LCD_WriteData(0x33);

	LCD_WriteCmd(0xB7);
	LCD_WriteData(0x35);

	LCD_WriteCmd(0xBB);       //vcom
	LCD_WriteData(0x32);      //30

	LCD_WriteCmd(0xC0);
	LCD_WriteData(0x0C);

	LCD_WriteCmd(0xC2);
	LCD_WriteData(0x01);

	LCD_WriteCmd(0xC3);       //vrh
	LCD_WriteData(0x10);      //17 0D

	LCD_WriteCmd(0xC4);       //vdv
	LCD_WriteData(0x20);      //20

	LCD_WriteCmd(0xC6);
	LCD_WriteData(0x0f);

	LCD_WriteCmd(0xD0);
	LCD_WriteData(0xA4);
	LCD_WriteData(0xA1);

	LCD_WriteCmd(0xE0);       //Set Gamma
	LCD_WriteData(0xd0);
	LCD_WriteData(0x00);
	LCD_WriteData(0x02);
	LCD_WriteData(0x07);
	LCD_WriteData(0x0a);
	LCD_WriteData(0x28);
	LCD_WriteData(0x32);
	LCD_WriteData(0X44);
	LCD_WriteData(0x42);
	LCD_WriteData(0x06);
	LCD_WriteData(0x0e);
	LCD_WriteData(0x12);
	LCD_WriteData(0x14);
	LCD_WriteData(0x17);


	LCD_WriteCmd(0XE1);       //Set Gamma
	LCD_WriteData(0xd0);
	LCD_WriteData(0x00);
	LCD_WriteData(0x02);
	LCD_WriteData(0x07);
	LCD_WriteData(0x0a);
	LCD_WriteData(0x28);
	LCD_WriteData(0x31);
	LCD_WriteData(0x54);
	LCD_WriteData(0x47);
	LCD_WriteData(0x0e);
	LCD_WriteData(0x1c);
	LCD_WriteData(0x17);
	LCD_WriteData(0x1b);
	LCD_WriteData(0x1e);


	LCD_WriteCmd(0x2A);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0xef);

	LCD_WriteCmd(0x2B);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x3f);

	LCD_WriteCmd(0x29);  
}
/*
	控制背光，ENABLE开启，DISABLE关闭
*/
void LCD_BL(FunctionalState State)
{
	if(State)
	{
		GPIO_SetBits(ILI9341_BL_PORT,ILI9341_BL_Pin);		
	}
	else
	{
		GPIO_ResetBits(ILI9341_BL_PORT,ILI9341_BL_Pin);		
	}
}
/*
	初始化LCD液晶显示器扫描方向为从左到右，从上到下
	初始化完成后开启背光，设置背景色
*/
void LCD_Init(void)
{
	GPIO_Config();
	FSMC_Config();
	delay_ms(50);
	LCD_Config();
	LCD_BL(ENABLE);
	LCD_DrawRecFull(0,0,240,320,BackColor);
}
//写入数据
__inline void LCD_WriteData(u16 data)
{
	ILI9341_DATA=data;
}
//写入指令
__inline void LCD_WriteCmd(u16 cmd)
{
	ILI9341_CMD=cmd;
}
/*
	读数据
return:两字节
*/
__inline u16 LCD_Read(void)
{
	return ILI9341_DATA;
}

/*
读像素格式
return:两字节
*/
u16 LCD_ReadPixel(void)
{
	LCD_WriteCmd(0x0C);
	LCD_Read();
	return LCD_Read();
}
/*
	读液晶驱动器ID
*/
u16 LCD_ReadId(void)
{
	u16 id=0;
	LCD_WriteCmd(0X04);
	id=LCD_Read();
 	id=LCD_Read();
	id|=LCD_Read();
	id <<=8;
	id|=LCD_Read();

	return id;
}
/*
	设置光标位置
*/
void LCD_SetCursor(u16 x,u16 y)
{
	//设定X坐标，仅传入起点坐标
	LCD_WriteCmd(0x2A);
	LCD_WriteData((x&0xFF00)>>8);
	LCD_WriteData(x);
	//设定Y坐标，仅传入起点坐标
	LCD_WriteCmd(0x2B);
	LCD_WriteData((y&0xFF00)>>8);
	LCD_WriteData(y);
}
/*
			开窗指令
para1:窗口X坐标
para2:窗口Y坐标
para3:X方向长度
para4:Y方向长度
*/
void LCD_OpenWindow(u16 x,u16 y,u16 usWidth,u16 usHight)
{
	//设置X起点和终点
	LCD_WriteCmd(0x2A);
	LCD_WriteData(x>>8);
	LCD_WriteData(x&0xFF);
	LCD_WriteData(((x+usWidth-1)&0xFF00)>>8);
	LCD_WriteData(x+usWidth-1);
	//设置Y起点和终点
	LCD_WriteCmd(0x2B);
	LCD_WriteData(y>>8);
	LCD_WriteData(y&0xFF);
	LCD_WriteData(((y+usHight-1)&0xFF00)>>8);
	LCD_WriteData(y+usHight-1);
}
/*
	画一个点
para1:X坐标
para2:Y坐标
para3:颜色
*/
void DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_SetCursor(x,y);
	LCD_WriteCmd(0x2C);
	LCD_WriteData(color);
}
void LCD_DrawLine(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	int16_t Delx,Dely,Dis;
	uint16_t Monx=0,Mony=0;
	u16 Curx,Cury;
	int16_t dx,dy,i;
	Curx=sx;	Cury=sy;
	Delx=ex-sx;	Dely=ey-sy;
	if(Delx>0){dx=1;}	else{dx=-1; Delx=-Delx;}
	if(Dely>0){dy=1;}	else{dy=-1; Dely=-Dely;}
	if(Delx>Dely){Dis=Delx;}	else{Dis=Dely;}
	for(i=0;i<Dis+1;i++)
	{
		DrawPoint(Curx,Cury,color);
		Monx+=Delx;	Mony+=Dely;
		if(Monx>=Dis){Monx-=Dis;	Curx+=dx;}
		if(Mony>=Dis){Mony-=Dis;	Cury+=dy;}
	}
}
void LCD_DrawRecFull(u16 x,u16 y,u16 usWidth,u16 usHight,u16 color)
{
	u32 i;
	LCD_OpenWindow(x,y,usWidth,usHight);
	LCD_WriteCmd(0x2C);
	for(i=0;i<usWidth * usHight;i++)
	{
		LCD_WriteData(color);
	}
}
void LCD_DrawRecEmpty(u16 x,u16 y,u16 usWidth,u16 usHight,u16 color)
{
	LCD_OpenWindow(x,y,usWidth,usHight);
	LCD_DrawLine(x,y,x+usWidth-1,y,color);
	LCD_DrawLine(x,y,x,y+usHight-1,color);
	LCD_DrawLine(x+usWidth-1,y,x+usWidth-1,y+usHight-1,color);
	LCD_DrawLine(x,y+usHight-1,x+usWidth-1,y+usHight-1,color);
}
/*
------------------------------------------------------------
模式0：				.		模式1：		.	模式2：			.	模式3：					
					A		.					A		.		A					.		A									
					|		.					|		.		|					.		|							
					Y		.					X		.		Y					.		X					
					0		.					1		.		2					.		3					
	<--- X0 o		.	<----Y1	o		.		o 2X--->  .		o 3Y--->	
------------------------------------------------------------	
模式4：				.	模式5：			.	模式6：			.	模式7：					
	<--- X4 o		.	<--- Y5 o		.		o 6X--->  .		o 7Y--->	
					4		.					5		.		6					.		7	
					Y		.					X		.		Y					.		X						
					|		.					|		.		|					.		|							
					V		.					V		.		V					.		V		
---------------------------------------------------------		
*/
void LCD_GramSet(u8 dir)
{
	grammode=dir;
	if(dir%2){XSide=ShortSide;YSide=LongSide;}
	else{XSide=LongSide;YSide=ShortSide;}
	LCD_WriteCmd(0x36);
	LCD_WriteData(dir);
}
void LCD_ShowChar_EN(u16 x,u16 y,const char word)
{
	u8 ByteCount,BitCount,FontLength,Relation;
	Relation=word-' ';
	FontLength=CurFont->Hight*CurFont->Width/8;
	LCD_OpenWindow(x,y,CurFont->Width,CurFont->Hight);
	LCD_WriteCmd(0x2C);
	for(ByteCount=0;ByteCount<FontLength;ByteCount++)
	{
		for(BitCount=0;BitCount<8;BitCount++)
		{
			if((0x80>>BitCount)&*(CurFont->Table+Relation*FontLength+ByteCount))
			{LCD_WriteData(FrontColor);}
			else{LCD_WriteData(BackColor);}
		}
	}
}
/*

*/
void lCD_ShowStr_EN(u16 x,u16 y,char * pStr)
{
	u16 count=0;
	while(*pStr!='\0')
	{
		/*
		自动换行操作，可注释掉
		换行操作为一行后从下一行定义的X_Star位置开始，触底后从点X_Star和Y_Star位置开始
		*/
		if(x+count*CurFont->Width>239){y+=CurFont->Hight;x=X_Star;}
		if(y+count*CurFont->Hight>319){x=X_Star;y=Y_Star;}
		LCD_ShowChar_EN(x,y,*pStr);
		pStr++;
		x+=CurFont->Width;
	}
}
