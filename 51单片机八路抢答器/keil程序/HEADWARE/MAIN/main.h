#ifndef _MAIN_H_
#define _MAIN_H_

#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit run_key = P3^2;	//������
sbit rst_key = P3^3;	//��λ��
sbit add_key = P3^6;	//��ʱ��
sbit dec_key = P3^7;	//��ʱ��
sbit buzzer  = P3^5;	//������
sbit sta_led = P3^0;	//����ָʾ
sbit ans_led = P3^1;	//����ָʾ

#endif