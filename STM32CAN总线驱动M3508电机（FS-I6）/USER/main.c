#include "main.h"

unsigned char i;          										 //计数变量
unsigned char Send_Count; 										 //串口需要发送的字节数

extern u8  TIM2CH1_CAPTURE_STA;	//CH1
extern u16 TIM2CH1_CAPTURE_VAL;
extern u8  TIM2CH2_CAPTURE_STA;	//CH2
extern u16 TIM2CH2_CAPTURE_VAL;
extern u8  TIM2CH3_CAPTURE_STA;	//CH3
extern u16 TIM2CH3_CAPTURE_VAL;
extern u8  TIM2CH4_CAPTURE_STA;	//CH4
extern u16 TIM2CH4_CAPTURE_VAL;
extern u8  TIM1CH1_CAPTURE_STA;	//CH5
extern u16 TIM1CH1_CAPTURE_VAL;
extern u8  TIM1CH4_CAPTURE_STA;	//CH6
extern u16 TIM1CH4_CAPTURE_VAL;

u32 ch1,ch2,ch3,ch4,ch5,ch6;

int main(void)
{	
	delay_init();	
	LED_Init();		  		
	KEY_Init();		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	uart_init(128000);	
	USART3_Init(9600);
	
	TIM3_Int_Init(9,7199);	//1ms
	TIM2_Cap_Init(0XFFFF,72-1);		//以1Mhz的频率计数
	TIM1_Cap_Init(0XFFFF,0);		//以1Mhz的频率计数 
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_5tq,CAN_BS2_3tq,4,CAN_Mode_Normal);//CAN初始化普通模式,波特率1Mbps 
	Pid_ChassisSpeedInit();
	PidChassisPosInit();
	ZeroCheck_Init();	
	while(1)
	{	
//		Motor_motion_control();
//		//DataScope用
////		DataScope_Get_Channel_Data(PidChassisSpeed[0].SetPoint, 1 );
////		DataScope_Get_Channel_Data(motor_3508[0].speed, 2 );
////		Send_Count=DataScope_Data_Generate(2);
////		for( i = 0 ; i < Send_Count; i++) 
////		{
////			while((USART1->SR&0X40)==0);  
////			USART1->DR = DataScope_OutPut_Buffer[i]; 
////		}
////		delay_ms(50); //20HZ
//		
////		Motor_motion_control();
		
		//TIM2ch1 通道1-PA0
		if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			ch1=TIM2CH1_CAPTURE_STA&0X3F;		//溢出的次数
			ch1*=65536;					//溢出时间总和
			ch1+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
			printf("ch1:%d us\r\n",ch1);	//打印总的高点平时间
 			TIM2CH1_CAPTURE_STA=0;			//开启下一次捕获
		}
		
		//TIM2ch2 通道2-PA1
		if(TIM2CH2_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			ch2=TIM2CH2_CAPTURE_STA&0X3F;		//溢出的次数
			ch2*=65536;					//溢出时间总和
			ch2+=TIM2CH2_CAPTURE_VAL;		//得到总的高电平时间
			printf("ch2:%d us\r\n",ch2);	//打印总的高点平时间
 			TIM2CH2_CAPTURE_STA=0;			//开启下一次捕获
		}
		
		//TIM2ch3 通道3-PA2
		if(TIM2CH3_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			ch3=TIM2CH3_CAPTURE_STA&0X3F;		//溢出的次数
			ch3*=65536;					//溢出时间总和
			ch3+=TIM2CH3_CAPTURE_VAL;		//得到总的高电平时间
			printf("ch3:%d us\r\n",ch3);	//打印总的高点平时间
 			TIM2CH3_CAPTURE_STA=0;			//开启下一次捕获
		}
		
		//TIM2ch4 通道4-PA3
		if(TIM2CH4_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			ch4=TIM2CH4_CAPTURE_STA&0X3F;		//溢出的次数
			ch4*=65536;					//溢出时间总和
			ch4+=TIM2CH4_CAPTURE_VAL;		//得到总的高电平时间
			printf("ch4:%d us\r\n",ch4);	//打印总的高点平时间
 			TIM2CH4_CAPTURE_STA=0;			//开启下一次捕获
		}
//		//TIM1ch1 通道5
//		if(TIM1CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
//		{
//			ch5=TIM1CH1_CAPTURE_STA&0X3F;		//溢出的次数
//			ch5*=65536;					//溢出时间总和
//			ch5+=TIM1CH1_CAPTURE_VAL;		//得到总的高电平时间
//			printf("ch5:%d us\r\n",ch5);	//打印总的高点平时间
// 			TIM1CH1_CAPTURE_STA=0;			//开启下一次捕获
//		}
//		//TIM1ch4 通道6
//		if(TIM1CH4_CAPTURE_STA&0X80)//成功捕获到了一次高电平
//		{
//			ch6=TIM1CH4_CAPTURE_STA&0X3F;		//溢出的次数
//			ch6*=65536;					//溢出时间总和
//			ch6+=TIM1CH4_CAPTURE_VAL;		//得到总的高电平时间
//			printf("ch6:%d us\r\n",ch6);	//打印总的高点平时间
// 			TIM1CH4_CAPTURE_STA=0;			//开启下一次捕获		
// 		}			
		
		if((ch1>1200 && ch1<1800) && ch2>1900)
			chassis_forward(set_speed);					//前
		else if(ch1>1200 && ch2<1000)
			chassis_back(set_speed);					//后
		else if(ch1<1000 && (ch2>1350 && ch2<1500))
			chassis_left(set_speed);					//左移
		else if(ch1>1900 && (ch2>1350 && ch2<1500))
			chassis_right(set_speed);					//右移
		else if(ch1<1100 && ch2>1900)
			chassis_leftrota(set_speed);				//逆旋
		else if(ch1>1900 && ch2>1900)	
			chassis_rightrota(set_speed);				//顺旋
//		else if(ch3>900 && ch3<1350)
//			set_speed = 0,chassis_mode(),flag=0;
//		else if(ch3>1400 && ch3<1500)
//			set_speed = 2000,chassis_mode(),flag=0;
//		else if(ch3>1900)
//			set_speed = 4000;
		else
			chassis_stop();		
	}
}
