#include "main.h"

//------------�ڲ���������-----------------//
int16_t motor_cur_out[4];
float zerocheck_out,zerocheck_last_out,real_pos;

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}

/** 
  * @brief  ��ʱ��3�жϴ���,3508�������,�ٶ�PID����
  * @param  None
  * @retval 
  */
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	short i;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  	//���TIMx�����жϱ�־ 
		
		zerocheck_out = ZeroCheck_Cal(&ZeroCheck_Chassis[1],motor_3508[1].angle);
		real_pos = ((zerocheck_out - zerocheck_last_out)/8192.f*360)/1.f;
		zerocheck_last_out = zerocheck_out;
		
		for(i=0;i<4;i++)
		{	
//			PidChassisPos[i].ActPoint = ZeroCheck_Cal(&ZeroCheck_Chassis[i],motor_3508[i].angle);
//			PidChassisSpeed[i].SetPoint=LIMIT_MAX_MIN(Pid_Calc(&PidChassisPos[i],PidChassisPos[i].SetPoint),8000,-8000);
			
			PidChassisSpeed[i].ActPoint = motor_3508[i].speed;
			motor_cur_out[i] = (short)LIMIT_MAX_MIN(Pid_Calc(&PidChassisSpeed[i],PidChassisSpeed[i].SetPoint),16000,-16000);
		}				
		Can_Motor_SetCur(motor_cur_out[0],motor_cur_out[1],motor_cur_out[2],motor_cur_out[3]);	
		
	}
}


