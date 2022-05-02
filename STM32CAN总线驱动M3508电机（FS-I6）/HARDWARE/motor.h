#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"

typedef struct
{
	int16_t angle;		//角度 0~8191
	int16_t speed;		//转速
	int16_t current;	//电流值
	uint8_t temperature;
}Motor_Measure;

extern Motor_Measure motor_3508[4];
extern short set_speed;
extern u8 Flag,run_flag;

extern u8 Can_Motor_SetCur(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
extern void get_motor_measure(Motor_Measure *ptr, CanRxMsg* RxMessage);

extern void chassis_forward(short M3508_Setpoint);
extern void chassis_back(short M3508_Setpoint);
extern void chassis_left(short M3508_Setpoint);
extern void chassis_right(short M3508_Setpoint);
extern void chassis_stop(void);
extern void chassis_rightrota(short M3508_Setpoint);
extern void chassis_leftrota(short M3508_Setpoint);

extern void chassis_mode(void);
extern void Motor_motion_control(void);

#endif
