#include "main.h"

PID_Typedef PidChassisSpeed[4],PidChassisPos[4];

/** 
  * @brief  PID�����㷨
  * @param  PID_Typedef *Pid  PID�ṹ��ָ��
			float setpoint    ����ٶ��趨ֵ
  * @retval PID���㷴�����
  */
float Pid_Calc(PID_Typedef *Pid,float setpoint)
{
	Pid->SetPoint = setpoint;
	
	Pid->Pre_err = Pid->SetPoint - Pid->ActPoint;
	
//	if(ABS(Pid->Pre_err) > Pid->Deadband)
//		Pid->Pre_err = Pid->Pre_err;
//	if(ABS(Pid->Pre_err) < Pid->Deadband)
//		Pid->Pre_err = 0;
	
	Pid->D_err = Pid->Pre_err - Pid->Last_err;
	
	Pid->Sum_err += Pid->Pre_err;
	Pid->Last_err =Pid->Pre_err;
	
	if(Pid->Sum_err >= Pid->I_Max)
		Pid->Sum_err = Pid->I_Max;
	else if(Pid->Sum_err <= -Pid->I_Max)
		Pid->Sum_err = -Pid->I_Max;
	
	Pid->POut = Pid->P * Pid->Pre_err;
	Pid->IOut = Pid->I * Pid->Sum_err;
	Pid->DOut = Pid->D * Pid->D_err;
	
	return Pid->POut + Pid->IOut + Pid->DOut;
}

/**
  * @brief  ���̵���ٶ�PID������ʼ��
  * @param  None
  * @retval None
  */
void Pid_ChassisSpeedInit(void)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		PidChassisSpeed[i].SetPoint = 0;	//-10000~10000
//		PidChassisSpeed[i].Deadband = 30;
		PidChassisSpeed[i].P = 8.0f;
		PidChassisSpeed[i].I = 0.1f;
		PidChassisSpeed[i].D = 0.0f;
		PidChassisSpeed[i].I_Max = 100.0f;
	}
}

/**
  * @brief  ���̵��λ��PID������ʼ��
  * @param  None
  * @retval None
  */
void PidChassisPosInit(void)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		PidChassisPos[i].SetPoint = 0;	   	
		PidChassisPos[i].P = 1.0f;
		PidChassisPos[i].I = 0.0f;
		PidChassisPos[i].D = 0.0f;
		PidChassisPos[i].I_Max = 100.0f;
	}
}
