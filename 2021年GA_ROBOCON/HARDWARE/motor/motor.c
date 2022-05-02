#include "sys.h"
#include "motor.h"


void Motor_Init()
{
	GPIO_InitTypeDef   GPIO_InitStruct; 
// 8个 IN 的配置和初始化	
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟

  RCC_APB2PeriphClockCmd(PWMA_GPIO_CLK | PWMB_GPIO_CLK| PWMC_GPIO_CLK| PWMD_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟

	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5   

	
  //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.6 GPIOA.7
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = PWMA_GPIO_PIN|PWMB_GPIO_PIN; //TIM_CH1 TIM_CH2
    
	GPIO_Init(PWMA_GPIO_PORT, &GPIO_InitStructure);//初始化GPIO
	GPIO_Init(PWMB_GPIO_PORT, &GPIO_InitStructure);//初始化GPIO
    
  GPIO_InitStructure.GPIO_Pin = PWMC_GPIO_PIN|PWMD_GPIO_PIN; //TIM_CH1 TIM_CH2
  GPIO_Init(PWMC_GPIO_PORT, &GPIO_InitStructure);//初始化GPIO
	GPIO_Init(PWMD_GPIO_PORT, &GPIO_InitStructure);//初始化GPIO

 
  //初始化TIM3

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值

	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	
    
 //初始化TIM3 Channel2 PWM模式   

 //------------------注意！！！----------------------//

 //在模式PWM1中有效电平于无效电平  such as (TIM_OCPolarity_Low)有效 则为低电平  否则无效电平为高电平

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
 	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
 	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
    
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
 	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
  TIM_Cmd(TIM3, ENABLE);  //使能TIM3

}



void A_go(u16  pwm)
{
    GPIO_SetBits(IN1_GPIO_PORT,IN1_GPIO_PIN);
	  GPIO_ResetBits(IN2_GPIO_PORT,IN2_GPIO_PIN);
    TIM_SetCompare1(TIM3,pwm);	//	电机1占空比  
}

void A_back(u16 pwm)
{
    GPIO_ResetBits(IN1_GPIO_PORT,IN1_GPIO_PIN);
	GPIO_SetBits(IN2_GPIO_PORT,IN2_GPIO_PIN);
    TIM_SetCompare1(TIM3,pwm);	//	电机1占空比  
}


void B_go(u16  pwm)
{
    GPIO_SetBits(IN3_GPIO_PORT,IN3_GPIO_PIN);
	GPIO_ResetBits(IN4_GPIO_PORT,IN4_GPIO_PIN);
    TIM_SetCompare2(TIM3,pwm);	//	电机2占空
}

void B_back(u16 pwm)
{
    GPIO_ResetBits(IN3_GPIO_PORT,IN3_GPIO_PIN);
	GPIO_SetBits(IN4_GPIO_PORT,IN4_GPIO_PIN);
    TIM_SetCompare2(TIM3,pwm);	//	电机2占空
}

void C_go(u16   pwm)
{
     GPIO_SetBits(IN5_GPIO_PORT,IN5_GPIO_PIN);
	 GPIO_ResetBits(IN6_GPIO_PORT,IN6_GPIO_PIN);
     TIM_SetCompare3(TIM3,pwm);	//	电机1占空比  
}
void C_back(u16 pwm)
{
     GPIO_ResetBits(IN5_GPIO_PORT,IN5_GPIO_PIN);
	 GPIO_SetBits(IN6_GPIO_PORT,IN6_GPIO_PIN);
     TIM_SetCompare3(TIM3,pwm);	//	电机1占空比  
}

void D_go(u16  pwm)
{
    GPIO_SetBits(IN7_GPIO_PORT,IN7_GPIO_PIN);
	GPIO_ResetBits(IN8_GPIO_PORT,IN8_GPIO_PIN);
    TIM_SetCompare4(TIM3,pwm);	//	电机2占空比 
}
void D_back(u16 pwm)
{
    GPIO_ResetBits(IN7_GPIO_PORT,IN7_GPIO_PIN);
	GPIO_SetBits(IN8_GPIO_PORT,IN8_GPIO_PIN);
    TIM_SetCompare4(TIM3,pwm);	//	电机2占空比 
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
    
    TIM_SetCompare1(TIM3,0);	//	电机2占空比 
    TIM_SetCompare2(TIM3,0);	//	电机2占空比 
    TIM_SetCompare3(TIM3,0);	//	电机2占空比 
    TIM_SetCompare4(TIM3,0);	//	电机2占空比 
    
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
***  右移 ： A:正转  B：反转  C：反转   D：正转
*/
void right_yi(u16 speed)
{
      A_go(speed);
      B_back(speed);
      C_back(speed);
      D_go(speed); 
}

// 左移
void left_yi(u16 speed)
{
     A_back(speed);
     B_go(speed);
     C_go(speed);
     D_back(speed);
}

// 右转 A、D正转， B、C 不动
void right_zhuan(u16 speed)
{
    A_go(speed);  
    D_go(speed); 
        
  
    TIM_SetCompare2(TIM3,0);	//	电机2占空比 
    TIM_SetCompare3(TIM3,0);	//	电机2占空比 
   

}

void left_zhuan(u16 speed)
{
    TIM_SetCompare1(TIM3,0);	//	电机2占空比 
    TIM_SetCompare4(TIM3,0);	//	电机2占空比 
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





