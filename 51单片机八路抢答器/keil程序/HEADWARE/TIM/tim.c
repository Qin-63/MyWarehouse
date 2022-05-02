#include "reg52.h"
#include "main.h"
#include "tim.h"
#include "delay.h"

bit run_flag = 0;	//�����˰��¿�ʼ����־λ
bit time_off = 0;	//����ʱʱ�䵽��������������ɹ�

u8 player;			//ѡ�ְ����ļ�ֵ
u8 now_time = 30;	//����ʱʱ�䣬30s
u16 player_num = 0;	//ѡ�ֺ���

u8 a=0,b=0,c=0,d=0;	//���Ӵ������ͳ��
u8 e=0,f=0,g=0,h=0;

u16 Count_A = 0;	//��ʱ����������
u16 Count_B = 0;	//��ʱ����������

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
	TR0 = 0;		//�رն�ʱ��
	TR1 = 0;
}

void anser(void)	//�����������ִ�еĲ���
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
	/*����ģ��*/
	if(run_flag == 1)		//����ʼ
	{
		player = P1;		//��ȡ�˿ڵ�ƽ��ȷ������λ��
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
			case 0xff: break;		//��������
			default: player_num = 9;break;		//�������������ʾ9
		}
	}	
}

/*��ʱ��1�ж�*/
void Time1() interrupt 3
{
	TH1 = (65536-10000)/256;		//10ms
	TL1 = (65536-10000)%256;	
	Count_A++;				/*����ʱģ��*/
	Count_B++;
	if(Count_B<50)
		buzzer = 0;
	else 
		buzzer = 1;
	
	if(Count_A == 100)		//ÿ���Ӽ�һ
	{
		Count_A = 0;
		now_time--;			//����ʱ��һ
		if(now_time <= 0)	//����ʱ�������������ܸ�λ������������
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