#include "main.h"

ZeroCheck_Typedef ZeroCheck_Chassis[4];

/**
  * @brief  λ��ʽ���ٶ�ʽ������
				Zero->ActualValue ��ʾ�������ǰֵ
				Zero->LastValue ��ʾ�������һ��ֵ
				Zero->CountCycle ��ʾ���������ʱԽ��ֵ������������
				Zero->PreError ��ʾ�������ֵ
			ʹ�ô˺���ǰҪ������Ӧ������ṹ��� Zero->CountCycle��Zero->LastValue
  * @param  ZeroCheck_Typedef *Zero  ������ṹ��
  *         float value  �������          
  * @retval ����������λ��ֵ
  */
float ZeroCheck_Cal(ZeroCheck_Typedef *Zero,float value)
{
	Zero->ActualValue=value;
	
	Zero->PreError=Zero->ActualValue-Zero->LastValue;
	Zero->LastValue=Zero->ActualValue;
	
	if(Zero->PreError>0.6f*Zero->CountCycle)
	{
		Zero->PreError=Zero->PreError-Zero->CountCycle;
		Zero->Circle++;
	}
	if(Zero->PreError<-0.6f*Zero->CountCycle)
	{
		Zero->PreError=Zero->PreError+Zero->CountCycle;
		Zero->Circle--;
	}
	return Zero->ActualValue - Zero->Circle*Zero->CountCycle;	
}

/**
  * @brief  ������ṹ�������ʼ��
  * @param  None
  * @retval None
  */
void ZeroCheck_Init(void)
{
	short i;
	for(i=0;i<4;i++)
	{
		ZeroCheck_Chassis[i].CountCycle = 8192;
		ZeroCheck_Chassis[i].LastValue = motor_3508[i].angle;
		ZeroCheck_Chassis[i].Circle = 0;
	}	
}
		
	
	

