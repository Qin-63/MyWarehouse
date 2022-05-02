#ifndef __ZEROCHECKTASK_H__
#define __ZEROCHECKTASK_H__

typedef struct 
{
	float Circle;           //转过圈数
	float CountCycle;       //转过一圈的总计数周期
	float LastValue;        //检测过零量上一次的值	
	float ActualValue;      //检测过零量当前值
	float PreError;         //检测量判断差值
}
ZeroCheck_Typedef;

extern ZeroCheck_Typedef ZeroCheck_Chassis[4];

extern float ZeroCheck_Cal(ZeroCheck_Typedef *Zero,float value);
extern void ZeroCheck_Init(void);

#endif
