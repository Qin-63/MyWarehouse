#include "reg52.h"
#include "tim.h"
#include "key.h"
#include "delay.h"

u8 next_time;

void KeyScan()		
{
	if(run_key == 0)		//��ʼ������
	{
		delay(10);
		if(run_key == 0)
		{
			sta_led = 0;
			ans_led = 1;
			run_flag = 1;	//����ģʽ
			buzzer = 0;		//��������
			TR0 = 1;		//������ʱ��������ʱ
			TR1 = 1;
		}
		while(run_key == 0);	//�����ɿ�
	}
 	if(rst_key == 0)		//��λ������
	{
		delay(10);
		if(rst_key == 0)
		{
			sta_led = 0;
			ans_led = 0;
			run_flag = 0;	//������
			TR0 = 0;		//�رն�ʱ��
			TR1 = 0;
			Count_A = 0;	//��ʱ��λ
			Count_B = 0;
			player_num = 0;
			time_off = 0;
			now_time = next_time;	//���¸�ֵ����ʱ
			buzzer = 1;		//ȡ������
		}
		while(rst_key == 0);
	}
   	if(run_flag==0 && time_off==0 )		//δ��ʼ����ʱ�򷽿ɼӼ�����ʱʱ��
	{
		if(add_key == 0)	//��ʱ��
		{
			delay(10);
			if(add_key == 0)
			{
				next_time = next_time+10;
				now_time = now_time+10;
			}
			while(add_key == 0);
		}
		if(dec_key == 0)	//��ʱ��
		{
			delay(10);
			if(dec_key == 0)
			{
				next_time = next_time - 10;
				now_time = now_time - 10;
			}
			while(dec_key == 0);
		}

		/*�������ͳ��ģ��*/
		player = P1;		//��ȡ�˿ڵ�ƽ��ȷ������λ��
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