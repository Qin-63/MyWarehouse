#include "wheel.h"

/*******************************定时器3 车轮控制*************************************/

void TIM3_PWM_Init(u16 arr,u16 psc){  //TIM3 PWM初始化 arr重装载值 psc预分频系数
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3和相关GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOB时钟(LED在PB0引脚)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能AFIO时钟(定时器3通道3需要重映射到BP5引脚)
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;     // TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // 复用推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
    GPIO_Init(GPIOB,&GPIO_InitStrue);                //GPIO端口初始化设置
	
	  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;     // TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // 复用推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
    GPIO_Init(GPIOA,&GPIO_InitStrue);                //GPIO端口初始化设置
	
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;     // TIM_CH3
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;       // 复用推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
    GPIO_Init(GPIOC,&GPIO_InitStrue);                //GPIO端口初始化设置 
		
//    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //映射，重映射只用于64、100、144脚单片机
   //当没有重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PA6，PA7,PB0,PB1
   //当部分重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PB4，PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
   //当完全重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PC6，PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr;    //设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        //TIM3初始化设置(设置PWM的周期)
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWM模式1:CNT < CCR时输出有效电平
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道3 PWM 模式设置
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);        //使能预装载寄存器
	
	
/***********TIM3_CH1***************/
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWM模式1:CNT < CCR时输出有效电平
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道3 PWM 模式设置
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);        //使能预装载寄存器

/***********TIM3_CH2***************/	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWM模式1:CNT < CCR时输出有效电平
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
    TIM_OC2Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道3 PWM 模式设置
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        //使能预装载寄存器

/***********TIM3_CH1***************/
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWM模式1:CNT < CCR时输出有效电平
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
    TIM_OC1Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道3 PWM 模式设置
    TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);        //使能预装载寄存器

/***********TIM3_CH1***************/
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWM模式1:CNT < CCR时输出有效电平
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
    TIM_OC4Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道3 PWM 模式设置
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);        //使能预装载寄存器
    
    TIM_Cmd(TIM3,ENABLE);        //使能TIM3
    
}
/********************************************************************/

/***************************车轮驱动io*****************************************/
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

void car_en_init(void)  //车轮使能端初始化
{
	GPIO_InitTypeDef     GPIO_InitStrue;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//使能GPIOB时钟(LED在PB0引脚)
		
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;     
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;    // 推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
    GPIO_Init(GPIOC,&GPIO_InitStrue);
	
	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;     
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;    // 推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
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
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
}


void car_back(int speed) 
{
	ctr.left_front_neg();
	ctr.left_back_neg();
	ctr.right_front_neg();
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
}

void car_left(int speed) 
{
	ctr.left_front_neg();
	ctr.left_back_pos();
	ctr.right_front_pos();
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
}

void car_right(int speed) 
{
	ctr.left_front_pos();
	ctr.left_back_neg();
	ctr.right_front_neg();
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
}

void car_right_rotation(int speed) 
{
	ctr.left_front_pos();
	ctr.left_back_pos();
	ctr.right_front_neg();
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
}


void car_left_rotation(int speed) 
{
	ctr.left_front_neg();
	ctr.left_back_neg();
	ctr.right_front_pos();
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
}


void car_left_front(int speed)
{
	PC13_1;PC1_1;   //悬空
	PC6_1;PD2_1;
	
	
	ctr.left_back_pos();	
	ctr.right_front_pos();
	
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
	/************其他两个通道清零**************/
	TIM_SetCompare1(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
}

void car_right_back(int speed)
{
	PC13_1;PC1_1;   //悬空
	PC6_1;PD2_1;   //左前和右后悬空
	
	
	ctr.left_back_neg();	
	ctr.right_front_neg();
	
	TIM_SetCompare2(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
	/************其他两个通道清零**************/
	TIM_SetCompare1(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
}


void car_left_back(int speed)
{
	PC14_1;PC3_1;   //悬空
	PC4_1;PC5_1;
	
	
	ctr.left_front_neg();	
	ctr.right_back_neg();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
	/************其他两个通道清零**************/
	TIM_SetCompare2(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
}


void car_right_front(int speed)
{
	PC14_1;PC3_1;   //悬空
	PC4_1;PC5_1;
	
	ctr.left_front_pos();	
	ctr.right_back_pos();
	
	TIM_SetCompare1(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare4(TIM3,speed);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
		/************其他两个通道清零**************/
	TIM_SetCompare2(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	TIM_SetCompare3(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	
}

