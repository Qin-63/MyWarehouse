#ifndef __PID_H__
#define __PID_H__

typedef struct
{
	float SetPoint;		//�趨ֵ
	float ActPoint;		//ʵ��ֵ(�ⶨֵ)
	float Deadband;		//����
	
	//PID����
	float P;
	float I;
	float D;
	
	float Last_err;		//�ϴ����
	float Pre_err;		//��ǰ���
	float Sum_err;		//�������(�ۼ����)
	float D_err;		//΢�����(���ϴ����)
	
	float I_Max;		//��������
	
	//PID���
	float POut;
	float IOut;
	float DOut;
	
}PID_Typedef;

extern PID_Typedef PidChassisSpeed[4],PidChassisPos[4];

extern void Pid_ChassisSpeedInit(void);
extern float Pid_Calc(PID_Typedef *Pid,float setpoint);
extern void PidChassisPosInit(void);

#endif
