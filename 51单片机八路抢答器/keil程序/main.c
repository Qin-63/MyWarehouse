#include "reg52.h"
#include "delay.h"
#include "key.h"
#include "seg.h"
#include "tim.h"
#include "main.h"

void main(void)
{
	EX_Init();
	buzzer = 1;
	P2 = 0xff;
	P1 = 0xff;
	P0 = 0xff;
	sta_led = 0;
	ans_led = 0;
	next_time = now_time;
	while(1)
	{	
		KeyScan();
		display(player_num,now_time);	
	}
}