#include "main.h"

ZeroCheck_Typedef ZeroCheck_Chassis[4];

/**
  * @brief  位置式和速度式过零检测
				Zero->ActualValue 表示检测量当前值
				Zero->LastValue 表示检测量上一次值
				Zero->CountCycle 表示检测量过零时越变值，即计数周期
				Zero->PreError 表示检测量差值
			使用此函数前要申明对应检测量结构体的 Zero->CountCycle与Zero->LastValue
  * @param  ZeroCheck_Typedef *Zero  过零检测结构体
  *         float value  待检测量          
  * @retval 输出过零检测后位置值
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
  * @brief  过零检测结构体参数初始化
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
		
	
	

