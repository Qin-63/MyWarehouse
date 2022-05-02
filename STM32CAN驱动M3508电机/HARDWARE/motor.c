#include "main.h"

//-----------------内部变量定义----------------//
Motor_Measure motor_3508[4];
short set_speed=1000;
u8 Flag,run_flag;

/**
  * @brief  CAN总线控制电机输出电流
  * @param  motorx 对应四个电机输出电流大小,范围[-16384,16384]
		       对应输出电流-20A~0~20A
  * @retval 
  */
u8 Can_Motor_SetCur(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x200;			// 标准标识符 
	TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=8;				// 要发送的数据长度
	
	motor1 = LIMIT_MAX_MIN(motor1,10000,-10000);
	motor2 = LIMIT_MAX_MIN(motor2,10000,-10000);
	motor3 = LIMIT_MAX_MIN(motor3,10000,-10000);
	motor4 = LIMIT_MAX_MIN(motor4,10000,-10000);
	
	TxMessage.Data[0] = motor1 >> 8;
	TxMessage.Data[1] = motor1;
	TxMessage.Data[2] = motor2 >> 8;
	TxMessage.Data[3] = motor2;
	TxMessage.Data[4] = motor3 >> 8;
	TxMessage.Data[5] = motor3;
	TxMessage.Data[6] = motor4 >> 8;
	TxMessage.Data[7] = motor4;			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0;
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
	if(i>=0XFFF)return 1;
	return 0;		
}

/**
  * @brief  电机反馈数据处理函数
  * @param  Motor_Measure *ptr  电机信息结构体指针
			CanRxMsg RxMessage  CAN数据接收结构体变量
  * @retval None
  */
void get_motor_measure(Motor_Measure *ptr, CanRxMsg* RxMessage)
{
	ptr->angle = (uint16_t)(RxMessage->Data[0]<<8 | RxMessage->Data[1]);
	ptr->speed = (uint16_t)(RxMessage->Data[2]<<8 | RxMessage->Data[3]);
	ptr->current = (int16_t)(RxMessage->Data[4]<<8 | RxMessage->Data[5]);
	ptr->temperature = RxMessage->Data[6];
}

/**
  * @brief  底盘前进函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_forward(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[1].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[2].SetPoint = M3508_Setpoint;
	PidChassisSpeed[3].SetPoint = M3508_Setpoint;
}

/**
  * @brief  底盘后退函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_back(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = M3508_Setpoint;
	PidChassisSpeed[1].SetPoint = M3508_Setpoint;
	PidChassisSpeed[2].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[3].SetPoint = -M3508_Setpoint;
}

/**
  * @brief  底盘左转函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_left(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = M3508_Setpoint;
	PidChassisSpeed[1].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[2].SetPoint = M3508_Setpoint;
	PidChassisSpeed[3].SetPoint = -M3508_Setpoint;
}

/**
  * @brief  底盘右转函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_right(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[1].SetPoint = M3508_Setpoint;
	PidChassisSpeed[2].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[3].SetPoint = M3508_Setpoint;
}

/**
  * @brief  底盘停止函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_stop(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = 0;
	PidChassisSpeed[1].SetPoint = 0;
	PidChassisSpeed[2].SetPoint = 0;
	PidChassisSpeed[3].SetPoint = 0;	
}

/**
  * @brief  底盘顺时针旋转函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_rightrota(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = M3508_Setpoint;
	PidChassisSpeed[1].SetPoint = M3508_Setpoint;
	PidChassisSpeed[2].SetPoint = M3508_Setpoint;
	PidChassisSpeed[3].SetPoint = M3508_Setpoint;	
}

/**
  * @brief  底盘逆时针旋转函数
  * @param 	short M3508_Setpoint 电机目标速度输入
  * @retval None
  */
void chassis_leftrota(short M3508_Setpoint)	
{
	PidChassisSpeed[0].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[1].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[2].SetPoint = -M3508_Setpoint;
	PidChassisSpeed[3].SetPoint = -M3508_Setpoint;	
}

/**
  * @brief  电机运动控制函数
  * @param 	None
  * @retval None
  */
void chassis_mode(void)
{
	switch(run_flag)
	{
		case 1:  chassis_forward(set_speed);break;
		case 2:  chassis_back(set_speed);break;
		case 3:  chassis_left(set_speed);break;
		case 4:  chassis_right(set_speed);break;
		case 5:  chassis_stop(set_speed);break;
		case 6:  chassis_rightrota(set_speed);break;
		case 7:  chassis_leftrota(set_speed);break;
		default: break;
	}
}
void Motor_motion_control(void)
{
	switch(Flag)
	{
		case 0x01: chassis_forward(set_speed);run_flag=1;Flag=0;break;			
		case 0x02: chassis_back(set_speed);run_flag=2;Flag=0;break;		
		case 0x03: chassis_left(set_speed);run_flag=3;Flag=0;break;		
		case 0x04: chassis_right(set_speed);run_flag=4;Flag=0;break;		
		case 0x05: chassis_stop(set_speed);run_flag=5;Flag=0;break;	
		case 0x06: chassis_rightrota(set_speed);run_flag=6;Flag=0;break;	
		case 0x07: chassis_leftrota(set_speed);run_flag=7;Flag=0;break;	

		case 0x08: set_speed+=1000; if(set_speed>5000) set_speed=5000; chassis_mode(); Flag=0;break;
		case 0x09: set_speed-=1000; if(set_speed<0) set_speed=0;chassis_mode(); Flag=0;break;
	}
}
	

