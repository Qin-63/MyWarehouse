#ifndef _TIMER_H_
#define _TIMER_H_
#include "reg52.h"
#include "main.h"

extern bit run_flag;	//�����˰��¿�ʼ����־λ
extern bit time_off;	//����ʱʱ�䵽��������������ɹ�
extern u8 player;			//ѡ�ְ����ļ�ֵ
extern u16 player_num;	//ѡ�ֺ���
extern u8 now_time;	//����ʱʱ�䣬30s
extern u8 a,b,c,d;	//���Ӵ������ͳ��
extern u8 e,f,g,h;
extern u16 Count_A;	//��ʱ����������
extern u16 Count_B;	//��ʱ����������

extern void EX_Init();

#endif