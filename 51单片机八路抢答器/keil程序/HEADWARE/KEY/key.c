#include "reg52.h"
#include "tim.h"
#include "key.h"
#include "delay.h"

u8 next_time;

void KeyScan()		
{
	if(run_key == 0)		//开始键按下
	{
		delay(10);
		if(run_key == 0)
		{
			sta_led = 0;
			ans_led = 1;
			run_flag = 1;	//设置模式
			buzzer = 0;		//蜂鸣器响
			TR0 = 1;		//开启定时器，倒计时
			TR1 = 1;
		}
		while(run_key == 0);	//按键松开
	}
 	if(rst_key == 0)		//复位键按下
	{
		delay(10);
		if(rst_key == 0)
		{
			sta_led = 0;
			ans_led = 0;
			run_flag = 0;	//不抢答
			TR0 = 0;		//关闭定时器
			TR1 = 0;
			Count_A = 0;	//定时复位
			Count_B = 0;
			player_num = 0;
			time_off = 0;
			now_time = next_time;	//重新赋值倒计时
			buzzer = 1;		//取消报警
		}
		while(rst_key == 0);
	}
   	if(run_flag==0 && time_off==0 )		//未开始抢答时候方可加减倒计时时间
	{
		if(add_key == 0)	//定时加
		{
			delay(10);
			if(add_key == 0)
			{
				next_time = next_time+10;
				now_time = now_time+10;
			}
			while(add_key == 0);
		}
		if(dec_key == 0)	//定时减
		{
			delay(10);
			if(dec_key == 0)
			{
				next_time = next_time - 10;
				now_time = now_time - 10;
			}
			while(dec_key == 0);
		}

		/*答题次数统计模块*/
		player = P1;		//读取端口电平，确定按键位置
		switch(player)
		{
			case 0xfe: player_num = 1;now_time = a;break;
			case 0xfd: player_num = 2;now_time = b;break;
			case 0xfb: player_num = 3;now_time = c;break;
			case 0xf7: player_num = 4;now_time = d;break;
			case 0xef: player_num = 5;now_time = e;break;
			case 0xdf: player_num = 6;now_time = f;break;
			case 0xbf: player_num = 7;now_time = g;break;
			case 0x7f: player_num = 8;now_time = h;break;
			case 0xff: break;		
		}
	}
}