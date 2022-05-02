#include "wheel.h"

/*******************************��ʱ��3 ���ֿ���*************************************/

void TIM3_PWM_Init(u16 arr,u16 psc){  //TIM3 PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3�����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOBʱ��(LED��PB0����)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��AFIOʱ��(��ʱ��3ͨ��3��Ҫ��ӳ�䵽BP5����)
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;     // TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOB,&GPIO_InitStrue);                //GPIO�˿ڳ�ʼ������
	
	  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;     // TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOA,&GPIO_InitStrue);                //GPIO�˿ڳ�ʼ������
	
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;     // TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;       // ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOC,&GPIO_InitStrue);                //GPIO�˿ڳ�ʼ������ 
		
//    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //ӳ�䣬��ӳ��ֻ����64��100��144�ŵ�Ƭ��
   //��û����ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPA6��PA7,PB0,PB1
   //��������ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPB4��PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
   //����ȫ��ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPC6��PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr;    //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        //TIM3��ʼ������(����PWM������)
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���
	
	
/***********TIM3_CH1***************/
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���

/***********TIM3_CH2***************/	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC2Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���

/***********TIM3_CH1***************/
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC1Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
    TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���

/***********TIM3_CH1***************/
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC4Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���
    
    TIM_Cmd(TIM3,ENABLE);        //ʹ��TIM3
    
}
/********************************************************************/

/***************************��������io*****************************************/
car_ctr ctr=
{
l_f_p,
l_f_n,
l_b_p,
l_b_n,
r_f_p,
r_f_n,
r_b_p,
r_b_n,	 		
};

void car_en_init(void)  //����ʹ�ܶ˳�ʼ��
{
	GPIO_InitTypeDef     GPIO_InitStrue;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//ʹ��GPIOBʱ��(LED��PB0����)
		
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;     
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;    // ����
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOC,&GPIO_InitStrue);
	
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;     
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;    // ����
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOD,&GPIO_InitStrue);
	brake();
}

void brake(void)
{
	PC13_0;
	PC1_0;
	PC14_0;
	PC3_0;
	PC4_0;
	PC5_0;
	PC6_0;
	PD2_0;
}

void l_f_p(void)
{
	PC13_1;PC1_0;
}
void l_f_n(void)
{
    PC13_0;PC1_1;
}
void l_b_p(void)
{
	PC14_1;PC3_0;
}
void l_b_n(void)
{
	PC14_0;PC3_1;
}
void r_f_p(void)
{
	PC4_1;PC5_0;
}
void r_f_n(void)
{
	PC4_0;PC5_1;
}
void r_b_p(void)
{
	PC6_1;PD2_0;
}
void r_b_n(void)
{
	PC6_0;PD2_1;
}

void car_advance(int speed) 
{
	
	ctr.left_front_pos();
	ctr.left_back_pos();
	ctr.right_front_pos();
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
}


void car_back(int speed) 
{
	ctr.left_front_neg();
	ctr.left_back_neg();
	ctr.right_front_neg();
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
}

void car_left(int speed) 
{
	ctr.left_front_neg();
	ctr.left_back_pos();
	ctr.right_front_pos();
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
}

void car_right(int speed) 
{
	ctr.left_front_pos();
	ctr.left_back_neg();
	ctr.right_front_neg();
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
}

void car_right_rotation(int speed) 
{
	ctr.left_front_pos();
	ctr.left_back_pos();
	ctr.right_front_neg();
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
}


void car_left_rotation(int speed) 
{
	ctr.left_front_neg();
	ctr.left_back_neg();
	ctr.right_front_pos();
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
}


void car_left_front(int speed)
{
	PC13_1;PC1_1;   //����
	PC6_1;PD2_1;
	
	
	ctr.left_back_pos();	
	ctr.right_front_pos();
	
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
	/************��������ͨ������**************/
	TIM_SetCompare1(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
}

void car_right_back(int speed)
{
	PC13_1;PC1_1;   //����
	PC6_1;PD2_1;   //��ǰ���Һ�����
	
	
	ctr.left_back_neg();	
	ctr.right_front_neg();
	
	TIM_SetCompare2(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
	/************��������ͨ������**************/
	TIM_SetCompare1(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
}


void car_left_back(int speed)
{
	PC14_1;PC3_1;   //����
	PC4_1;PC5_1;
	
	
	ctr.left_front_neg();	
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
	/************��������ͨ������**************/
	TIM_SetCompare2(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
}


void car_right_front(int speed)
{
	PC14_1;PC3_1;   //����
	PC4_1;PC5_1;
	
	ctr.left_front_pos();	
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare4(TIM3,speed);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
		/************��������ͨ������**************/
	TIM_SetCompare2(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	TIM_SetCompare3(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	
}

