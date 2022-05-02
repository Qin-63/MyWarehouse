#ifndef _TIMER_H_
#define _TIMER_H_
#include "reg52.h"
#include "main.h"

extern bit run_flag;	//主持人按下开始键标志位
extern bit time_off;	//倒计时时间到，或者有人抢答成功
extern u8 player;			//选手按键的键值
extern u16 player_num;	//选手号码
extern u8 now_time;	//倒计时时间，30s
extern u8 a,b,c,d;	//各队答题次数统计
extern u8 e,f,g,h;
extern u16 Count_A;	//定时器计数变量
extern u16 Count_B;	//定时器计数变量

extern void EX_Init();

#endif