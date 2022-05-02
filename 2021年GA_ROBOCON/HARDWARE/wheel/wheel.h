#ifndef  __WHEEL_H
#define  __WHEEL_H
#include "sys.h"

#define PC13_0  GPIO_ResetBits(GPIOC,GPIO_Pin_13); //c0改c13
#define PC13_1  GPIO_SetBits(GPIOC,GPIO_Pin_13);

#define PC1_0  GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
#define PC1_1  GPIO_SetBits(GPIOC,GPIO_Pin_1);

#define PC14_0  GPIO_ResetBits(GPIOC,GPIO_Pin_14); 
#define PC14_1  GPIO_SetBits(GPIOC,GPIO_Pin_14);

#define PC3_0  GPIO_ResetBits(GPIOC,GPIO_Pin_3); 
#define PC3_1  GPIO_SetBits(GPIOC,GPIO_Pin_3);

#define PC4_0  GPIO_ResetBits(GPIOC,GPIO_Pin_4); 
#define PC4_1  GPIO_SetBits(GPIOC,GPIO_Pin_4);

#define PC5_0  GPIO_ResetBits(GPIOC,GPIO_Pin_5); 
#define PC5_1  GPIO_SetBits(GPIOC,GPIO_Pin_5);

#define PC6_0  GPIO_ResetBits(GPIOC,GPIO_Pin_6); 
#define PC6_1  GPIO_SetBits(GPIOC,GPIO_Pin_6);

#define PD2_0  GPIO_ResetBits(GPIOD,GPIO_Pin_2); 
#define PD2_1  GPIO_SetBits(GPIOD,GPIO_Pin_2);


void TIM3_PWM_Init(u16 arr,u16 psc);

typedef struct
{
	void (*left_front_pos)(void);
    void (*left_front_neg)(void);
	void (*left_back_pos)(void);
	void (*left_back_neg)(void);
	void (*right_front_pos)(void);
    void (*right_front_neg)(void);
	void (*right_back_pos)(void);
	void (*right_back_neg)(void);
	 		
}car_ctr;
void (l_f_p)(void);
void (l_f_n)(void);
void (l_b_p)(void);
void (l_b_n)(void);
void (r_f_p)(void);
void (r_f_n)(void);
void (r_b_p)(void);
void (r_b_n)(void);
void brake(void);

void car_advance(int speed);

void car_back(int speed);


void car_left(int speed); 


void car_right(int speed); 


void car_left_rotation(int speed);


void car_right_rotation(int speed);

void car_left_front(int speed);

void car_right_back(int speed);


void car_left_back(int speed);
void car_en_init(void); //车轮使能端初始化



void car_right_front(int speed);

	
#endif

