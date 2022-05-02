#ifndef _MAIN_H_
#define _MAIN_H_

#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit run_key = P3^2;	//启动键
sbit rst_key = P3^3;	//复位键
sbit add_key = P3^6;	//定时加
sbit dec_key = P3^7;	//定时减
sbit buzzer  = P3^5;	//报警器
sbit sta_led = P3^0;	//抢答指示
sbit ans_led = P3^1;	//答题指示

#endif