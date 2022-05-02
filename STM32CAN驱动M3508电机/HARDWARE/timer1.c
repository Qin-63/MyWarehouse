#include "main.h"
	  

//��ʱ��2ͨ��1���벶������

TIM_ICInitTypeDef  TIM1_ICInitStructure;

void TIM1_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ʹ��TIM1ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);						 //PA0 ����
	
	//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM1_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  //TIM1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM1,ENABLE ); 	//ʹ�ܶ�ʱ��1
 
}


uint8_t  TIM1CH1_CAPTURE_STA1=0;	//���벶��״̬
u32 TIM1CH1_CAPTURE_VAL1=0;

void TIM1_CC_IRQHandler(void)
{
	if((TIM1CH1_CAPTURE_STA1&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM1CH1_CAPTURE_STA1&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM1CH1_CAPTURE_STA1&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM1CH1_CAPTURE_STA1|=0X80;//��ǳɹ�������һ��
					TIM1CH1_CAPTURE_VAL1=0XFFFF;
				}else TIM1CH1_CAPTURE_STA1++;
			}	 
		}
	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM1CH1_CAPTURE_STA1&0X40)		//����һ���½��� 		
			{	  			
				TIM1CH1_CAPTURE_STA1|=0X80;		//��ǳɹ�����һ��������
				TIM1CH1_CAPTURE_VAL1=TIM_GetCapture1(TIM1);
		   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM1CH1_CAPTURE_STA1=0;			//���
				TIM1CH1_CAPTURE_VAL1=0;
	 			TIM_SetCounter(TIM1,0);
				TIM1CH1_CAPTURE_STA1|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}




