#include "reg52.h"
#include "seg.h"

u8 code seven_seg[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};		//数码管段码0~9
u8 code seven_bit[] = {0xfe,0xfd,0xfb,0xf7};	//数码管位选

void display(u16 a,u16 b)	//a为选手号，b为时间
{
	P2 = seven_bit[0];
	P0 = seven_seg[a];	   		//选手号
	delay(1);
	P2 = seven_bit[1];
	P0 = 0x40;		//横杠
	delay(1);
	P2 = seven_bit[2];
	P0 = seven_seg[b/10];		//倒计时十位
	delay(1);
	P2 = seven_bit[3];
	P0 = seven_seg[b%10];		//倒计时个位
	delay(1);
	P2 = 0xff;		//消影	
}