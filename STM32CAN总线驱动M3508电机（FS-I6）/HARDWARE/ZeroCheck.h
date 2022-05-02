#ifndef __ZEROCHECKTASK_H__
#define __ZEROCHECKTASK_H__

typedef struct 
{
	float Circle;           //ת��Ȧ��
	float CountCycle;       //ת��һȦ���ܼ�������
	float LastValue;        //����������һ�ε�ֵ	
	float ActualValue;      //����������ǰֵ
	float PreError;         //������жϲ�ֵ
}
ZeroCheck_Typedef;

extern ZeroCheck_Typedef ZeroCheck_Chassis[4];

extern float ZeroCheck_Cal(ZeroCheck_Typedef *Zero,float value);
extern void ZeroCheck_Init(void);

#endif
