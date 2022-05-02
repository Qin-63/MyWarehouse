#ifndef __MOTOR_H
#define __MOTOR_H	 

#include "stm32f10x.h"

#define   IN1_GPIO_PIN       GPIO_Pin_11
#define   IN1_GPIO_PORT      GPIOF
#define   IN1_GPIO_CLK       RCC_APB2Periph_GPIOF

#define   IN2_GPIO_PIN       GPIO_Pin_13
#define   IN2_GPIO_PORT      GPIOF
#define   IN2_GPIO_CLK       RCC_APB2Periph_GPIOF
 
#define   IN3_GPIO_PIN       GPIO_Pin_15
#define   IN3_GPIO_PORT      GPIOF
#define   IN3_GPIO_CLK       RCC_APB2Periph_GPIOF

#define   IN4_GPIO_PIN       GPIO_Pin_1
#define   IN4_GPIO_PORT      GPIOG
#define   IN4_GPIO_CLK       RCC_APB2Periph_GPIOG


#define   IN5_GPIO_PIN       GPIO_Pin_8
#define   IN5_GPIO_PORT      GPIOE
#define   IN5_GPIO_CLK       RCC_APB2Periph_GPIOE

#define   IN6_GPIO_PIN       GPIO_Pin_10
#define   IN6_GPIO_PORT      GPIOE
#define   IN6_GPIO_CLK       RCC_APB2Periph_GPIOE
 
#define   IN7_GPIO_PIN       GPIO_Pin_12
#define   IN7_GPIO_PORT      GPIOE
#define   IN7_GPIO_CLK       RCC_APB2Periph_GPIOE

#define   IN8_GPIO_PIN       GPIO_Pin_14
#define   IN8_GPIO_PORT      GPIOE
#define   IN8_GPIO_CLK       RCC_APB2Periph_GPIOE


//PA7
#define   PWMA_GPIO_PIN       GPIO_Pin_7   
#define   PWMA_GPIO_PORT      GPIOA
#define   PWMA_GPIO_CLK       RCC_APB2Periph_GPIOA
//PA6
#define   PWMB_GPIO_PIN       GPIO_Pin_6
#define   PWMB_GPIO_PORT      GPIOA
#define   PWMB_GPIO_CLK       RCC_APB2Periph_GPIOA
//PB0
#define   PWMC_GPIO_PIN       GPIO_Pin_0
#define   PWMC_GPIO_PORT      GPIOB
#define   PWMC_GPIO_CLK       RCC_APB2Periph_GPIOB
//PB1
#define   PWMD_GPIO_PIN       GPIO_Pin_1
#define   PWMD_GPIO_PORT      GPIOB
#define   PWMD_GPIO_CLK       RCC_APB2Periph_GPIOB

void Motor_Init(void);
void TIM3_PWM_Init(u16 arr,u16 psc);

void A_go(u16   pwm);
void A_back(u16 pwm);
void B_go(u16   pwm);
void B_back(u16 pwm);
void C_go(u16   pwm);
void C_back(u16 pwm);
void D_go(u16   pwm);
void D_back(u16 pwm);


void stop(void);
void go_ahead(u16 speed);
void back(u16 speed);
void right_yi(u16 speed);
void left_yi(u16 speed);
void right_zhuan(u16 speed);
void left_zhuan(u16 speed);
void yuandizhuan(u16 speed);








#endif     /* __MOTOR_H	  */
