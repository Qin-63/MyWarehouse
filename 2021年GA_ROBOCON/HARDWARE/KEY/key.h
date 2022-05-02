#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键3 
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键4
#define KEY5  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取按键5


#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES	4		//KEY4
#define KEY5_PRES	5		//KEY5
#define KEY6_PRES	6		//KEY6  
#define KEY7_PRES	7		//KEY7 
#define KEY8_PRES	8		//KEY8  
#define KEY9_PRES	9		//KEY9
#define KEY10_PRES 10 //KEY10

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
