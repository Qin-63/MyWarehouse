#include "sys.h"
#include "motor.h"


void Motor_Init()
{
	GPIO_InitTypeDef   GPIO_InitStruct; 
// 8�� IN �����úͳ�ʼ��	
	RCC_APB2PeriphClockCmd(IN1_GPIO_CLK|IN2_GPIO_CLK|IN3_GPIO_CLK|IN4_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(IN5_GPIO_CLK|IN6_GPIO_CLK|IN7_GPIO_CLK|IN8_GPIO_CLK, ENABLE);
	
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
    
  GPIO_InitStruct.GPIO_Pin = IN1_GPIO_PIN|IN2_GPIO_PIN|IN3_GPIO_PIN|IN4_GPIO_PIN;
    
	GPIO_Init(IN1_GPIO_PORT,&GPIO_InitStruct);
	GPIO_Init(IN2_GPIO_PORT,&GPIO_InitStruct);
	GPIO_Init(IN3_GPIO_PORT,&GPIO_InitStruct);
	GPIO_Init(IN4_GPIO_PORT,&GPIO_InitStruct);
    
  GPIO_InitStruct.GPIO_Pin = IN5_GPIO_PIN|IN6_GPIO_PIN|IN7_GPIO_PIN|IN8_GPIO_PIN;
	
	GPIO_Init(IN5_GPIO_PORT,&GPIO_InitStruct);
	GPIO_Init(IN6_GPIO_PORT, &GPIO_InitStruct);
	GPIO_Init(IN7_GPIO_PORT,&GPIO_InitStruct);
	GPIO_Init(IN8_GPIO_PORT,&GPIO_InitStruct);
	
	
	GPIO_SetBits(IN1_GPIO_PORT, IN1_GPIO_PIN);
	GPIO_SetBits(IN2_GPIO_PORT, IN2_GPIO_PIN);
	GPIO_SetBits(IN3_GPIO_PORT, IN3_GPIO_PIN);
	GPIO_SetBits(IN4_GPIO_PORT, IN4_GPIO_PIN);
    GPIO_SetBits(IN5_GPIO_PORT, IN5_GPIO_PIN);
	GPIO_SetBits(IN6_GPIO_PORT, IN6_GPIO_PIN);
	GPIO_SetBits(IN7_GPIO_PORT, IN7_GPIO_PIN);
	GPIO_SetBits(IN8_GPIO_PORT, IN8_GPIO_PIN);

}

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��

  RCC_APB2PeriphClockCmd(PWMA_GPIO_CLK | PWMB_GPIO_CLK| PWMC_GPIO_CLK| PWMD_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5   

	
  //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.6 GPIOA.7
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = PWMA_GPIO_PIN|PWMB_GPIO_PIN; //TIM_CH1 TIM_CH2
    
	GPIO_Init(PWMA_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	GPIO_Init(PWMB_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO
    
  GPIO_InitStructure.GPIO_Pin = PWMC_GPIO_PIN|PWMD_GPIO_PIN; //TIM_CH1 TIM_CH2
  GPIO_Init(PWMC_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	GPIO_Init(PWMD_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO

 
  //��ʼ��TIM3

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ

	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	
    
 //��ʼ��TIM3 Channel2 PWMģʽ   

 //------------------ע�⣡����----------------------//

 //��ģʽPWM1����Ч��ƽ����Ч��ƽ  such as (TIM_OCPolarity_Low)��Ч ��Ϊ�͵�ƽ  ������Ч��ƽΪ�ߵ�ƽ

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
 	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
 	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
    
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
 	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
  TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3

}



void A_go(u16  pwm)
{
    GPIO_SetBits(IN1_GPIO_PORT,IN1_GPIO_PIN);
	  GPIO_ResetBits(IN2_GPIO_PORT,IN2_GPIO_PIN);
    TIM_SetCompare1(TIM3,pwm);	//	���1ռ�ձ�  
}

void A_back(u16 pwm)
{
    GPIO_ResetBits(IN1_GPIO_PORT,IN1_GPIO_PIN);
	GPIO_SetBits(IN2_GPIO_PORT,IN2_GPIO_PIN);
    TIM_SetCompare1(TIM3,pwm);	//	���1ռ�ձ�  
}


void B_go(u16  pwm)
{
    GPIO_SetBits(IN3_GPIO_PORT,IN3_GPIO_PIN);
	GPIO_ResetBits(IN4_GPIO_PORT,IN4_GPIO_PIN);
    TIM_SetCompare2(TIM3,pwm);	//	���2ռ��
}

void B_back(u16 pwm)
{
    GPIO_ResetBits(IN3_GPIO_PORT,IN3_GPIO_PIN);
	GPIO_SetBits(IN4_GPIO_PORT,IN4_GPIO_PIN);
    TIM_SetCompare2(TIM3,pwm);	//	���2ռ��
}

void C_go(u16   pwm)
{
     GPIO_SetBits(IN5_GPIO_PORT,IN5_GPIO_PIN);
	 GPIO_ResetBits(IN6_GPIO_PORT,IN6_GPIO_PIN);
     TIM_SetCompare3(TIM3,pwm);	//	���1ռ�ձ�  
}
void C_back(u16 pwm)
{
     GPIO_ResetBits(IN5_GPIO_PORT,IN5_GPIO_PIN);
	 GPIO_SetBits(IN6_GPIO_PORT,IN6_GPIO_PIN);
     TIM_SetCompare3(TIM3,pwm);	//	���1ռ�ձ�  
}

void D_go(u16  pwm)
{
    GPIO_SetBits(IN7_GPIO_PORT,IN7_GPIO_PIN);
	GPIO_ResetBits(IN8_GPIO_PORT,IN8_GPIO_PIN);
    TIM_SetCompare4(TIM3,pwm);	//	���2ռ�ձ� 
}
void D_back(u16 pwm)
{
    GPIO_ResetBits(IN7_GPIO_PORT,IN7_GPIO_PIN);
	GPIO_SetBits(IN8_GPIO_PORT,IN8_GPIO_PIN);
    TIM_SetCompare4(TIM3,pwm);	//	���2ռ�ձ� 
}


void stop(void)
{
    GPIO_ResetBits(IN1_GPIO_PORT,IN1_GPIO_PIN);
    GPIO_ResetBits(IN2_GPIO_PORT,IN2_GPIO_PIN);
    GPIO_ResetBits(IN3_GPIO_PORT,IN3_GPIO_PIN);
    GPIO_ResetBits(IN4_GPIO_PORT,IN4_GPIO_PIN);
    GPIO_ResetBits(IN5_GPIO_PORT,IN5_GPIO_PIN);
    GPIO_ResetBits(IN6_GPIO_PORT,IN6_GPIO_PIN);
    GPIO_ResetBits(IN7_GPIO_PORT,IN7_GPIO_PIN);
    GPIO_ResetBits(IN8_GPIO_PORT,IN8_GPIO_PIN);
    
    TIM_SetCompare1(TIM3,0);	//	���2ռ�ձ� 
    TIM_SetCompare2(TIM3,0);	//	���2ռ�ձ� 
    TIM_SetCompare3(TIM3,0);	//	���2ռ�ձ� 
    TIM_SetCompare4(TIM3,0);	//	���2ռ�ձ� 
    
}
void go_ahead(u16 speed)
{
    A_go(speed);
    B_go(speed);
    C_go(speed);
    D_go(speed); 
}

void back(u16 speed)
{
    A_back(speed);
    B_back(speed);
    C_back(speed);
    D_back(speed);
}

void qujian_h(u16 speed)
{
    A_back(23);
    B_back(20);
    C_back(23);
    D_back(20);
}

/*
***  ���� �� A:��ת  B����ת  C����ת   D����ת
*/
void right_yi(u16 speed)
{
      A_go(speed);
      B_back(speed);
      C_back(speed);
      D_go(speed); 
}

// ����
void left_yi(u16 speed)
{
     A_back(speed);
     B_go(speed);
     C_go(speed);
     D_back(speed);
}

// ��ת A��D��ת�� B��C ����
void right_zhuan(u16 speed)
{
    A_go(speed);  
    D_go(speed); 
        
  
    TIM_SetCompare2(TIM3,0);	//	���2ռ�ձ� 
    TIM_SetCompare3(TIM3,0);	//	���2ռ�ձ� 
   

}

void left_zhuan(u16 speed)
{
    TIM_SetCompare1(TIM3,0);	//	���2ռ�ձ� 
    TIM_SetCompare4(TIM3,0);	//	���2ռ�ձ� 
    B_go(speed);
    C_go(speed);
   
    
    
}

void yuandizhuan(u16 speed)
{
    A_go(speed);
    B_back(speed);
    C_go(speed);
    D_back(speed); 

}





