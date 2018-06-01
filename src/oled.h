//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
//中景园电子
//店铺地址：http://shop73023976.taobao.com/shop/view_shop.htm?tracelog=twddp&trace_log=qianniu_pc
//修改日期:2014/3/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//********************************************************************************
#ifndef _OLED_H
#define _OLED_H

#include "define.h"
#include "sleep.h"
#include "bmp.h"
#include "oledfont.h"

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define GPIO_CLK_PIN 54
#define GPIO_SDIN_PIN 55
#define GPIO_CS_PIN 56
#define GPIO_DC_PIN 57
#define GPIO_RST_PIN 58

//-----------------OLED端口定义(GPIO模仿SPI方式)----------------
#define OLED_SCLK_Clr() XGpioPs_WritePin(&gpio_display, GPIO_CLK_PIN ,0x0)// CLK(SCLK)
#define OLED_SCLK_Set() XGpioPs_WritePin(&gpio_display, GPIO_CLK_PIN ,0x1)

#define OLED_SDIN_Clr() XGpioPs_WritePin(&gpio_display, GPIO_SDIN_PIN ,0x0)// DIN(MOSI)
#define OLED_SDIN_Set() XGpioPs_WritePin(&gpio_display, GPIO_SDIN_PIN ,0x1)


#define OLED_CS_Clr()  XGpioPs_WritePin(&gpio_display, GPIO_CS_PIN ,0x0)// CS(SS)
#define OLED_CS_Set()  XGpioPs_WritePin(&gpio_display, GPIO_CS_PIN ,0x1)

#define OLED_DC_Clr() XGpioPs_WritePin(&gpio_display, GPIO_DC_PIN ,0x0)// D/C
#define OLED_DC_Set() XGpioPs_WritePin(&gpio_display, GPIO_DC_PIN ,0x1)

#define OLED_RST_Clr() XGpioPs_WritePin(&gpio_display, GPIO_RST_PIN ,0x0)// RES
#define OLED_RST_Set() XGpioPs_WritePin(&gpio_display, GPIO_RST_PIN ,0x1)

//端口初始化函数
void OLED_SCLK_INIT();
void OLED_SDIN_INIT();
void OLED_CS_INIT();
void OLED_DC_INIT();
void OLED_RST_INIT();


//------------------功能函数定义-------------------

//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



