#include "reg52.h"
#include "main.h"
#include "tim.h"
#include "delay.h"

bit run_flag = 0;	//主持人按下开始键标志位
bit time_off = 0;	//倒计时时间到，或者有人抢答成功

u8 player;			//选手按键的键值
u8 now_time = 30;	//倒计时时间，30s
u16 player_num = 0;	//选手号码

u8 a=0,b=0,c=0,d=0;	//各队答题次数统计
u8 e=0,f=0,g=0,h=0;

u16 Count_A = 0;	//定时器计数变量
u16 Count_B = 0;	//定时器计数变量

void EX_Init()
{
	TMOD = 0x11;
	TH0 = (65536-10000)/256;		//10ms
	TL0 = (65536-10000)%256;
	TH1 = (65536-10000)/256;		//10ms
	TL1 = (65536-10000)%256;
	IE = 0x8b;
	IT0 = 1;
	IT1 = 1;
	PX0 = 1;
	TR0 = 0;		//关闭定时器
	TR1 = 0;
}

void anser(void)	//有人抢答后所执行的操作
{
	run_flag = 0;
	time_off = 1;
	TR0 = 0;
	TR1 = 0;
	buzzer = 0;
	delay(200);
	buzzer = 1;
	sta_led = 1;
	ans_led = 0;
}

void Time0() interrupt 1
{
	TH0 = (65536-10000)/256;		//10ms
	TL0 = (65536-10000)%256;	
	/*抢答模块*/
	if(run_flag == 1)		//抢答开始
	{
		player = P1;		//读取端口电平，确定按键位置
		switch(player)
		{
			case 0xfe: player_num = 1;anser();a++;break;
			case 0xfd: player_num = 2;anser();b++;break;
			case 0xfb: player_num = 3;anser();c++;break;
			case 0xf7: player_num = 4;anser();d++;break;
			case 0xef: player_num = 5;anser();e++;break;
			case 0xdf: player_num = 6;anser();f++;break;
			case 0xbf: player_num = 7;anser();g++;break;
			case 0x7f: player_num = 8;anser();h++;break;
			case 0xff: break;		//无人抢答
			default: player_num = 9;break;		//出现其他情况显示9
		}
	}	
}

/*定时器1中断*/
void Time1() interrupt 3
{
	TH1 = (65536-10000)/256;		//10ms
	TL1 = (65536-10000)%256;	
	Count_A++;				/*倒计时模块*/
	Count_B++;
	if(Count_B<50)
		buzzer = 0;
	else 
		buzzer = 1;
	
	if(Count_A == 100)		//每秒钟减一
	{
		Count_A = 0;
		now_time--;			//倒计时减一
		if(now_time <= 0)	//倒计时结束，其他功能复位，蜂鸣器报警
		{
			 now_time = 0;
			 run_flag = 0;
			 TR0 = 0;
			 TR1 = 0;
			 time_off = 0;
			 buzzer = 0;
		}
	}
}