#include "main.h"

unsigned char i;          										 //计数变量
unsigned char Send_Count; 										 //串口需要发送的字节数
float zerocheck_out,zerocheck_last_out;
float real,speed_rpm;

int main(void)
{		
	delay_init();	
	LED_Init();		  		
	KEY_Init();		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	
	USART3_Init(9600);
	TIM3_Int_Init(9,7199);	//1ms
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_5tq,CAN_BS2_3tq,4,CAN_Mode_Normal);//CAN初始化普通模式,波特率1Mbps 
	Pid_ChassisSpeedInit();
	PidChassisPosInit();
	ZeroCheck_Init();	
	while(1)
	{	
//		//DataScope用
//		DataScope_Get_Channel_Data(PidChassisSpeed[0].SetPoint, 1 );
//		DataScope_Get_Channel_Data(motor_3508[0].speed, 2 );
//		Send_Count=DataScope_Data_Generate(2);
//		for( i = 0 ; i < Send_Count; i++) 
//		{
//			while((USART1->SR&0X40)==0);  
//			USART1->DR = DataScope_OutPut_Buffer[i]; 
//		}
//			delay_ms(50); //20HZ
		Motor_motion_control();
	}
}
