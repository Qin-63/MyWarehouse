#ifndef __PID_H__
#define __PID_H__

typedef struct
{
	float SetPoint;		//设定值
	float ActPoint;		//实际值(测定值)
	float Deadband;		//死区
	
	//PID参数
	float P;
	float I;
	float D;
	
	float Last_err;		//上次误差
	float Pre_err;		//当前误差
	float Sum_err;		//积分误差(累计误差)
	float D_err;		//微分误差(上上次误差)
	
	float I_Max;		//积分限制
	
	//PID输出
	float POut;
	float IOut;
	float DOut;
	
}PID_Typedef;

extern PID_Typedef PidChassisSpeed[4],PidChassisPos[4];

extern void Pid_ChassisSpeedInit(void);
extern float Pid_Calc(PID_Typedef *Pid,float setpoint);
extern void PidChassisPosInit(void);

#endif
