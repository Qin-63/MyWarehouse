#include "main.h"

unsigned char i;          										 //��������
unsigned char Send_Count; 										 //������Ҫ���͵��ֽ���

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	uart_init(128000);	
	USART3_Init(9600);
	
	TIM3_Int_Init(9,7199);	//1ms
	TIM2_Cap_Init(0XFFFF,72-1);		//��1Mhz��Ƶ�ʼ���
	TIM1_Cap_Init(0XFFFF,0);		//��1Mhz��Ƶ�ʼ��� 
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_5tq,CAN_BS2_3tq,4,CAN_Mode_Normal);//CAN��ʼ����ͨģʽ,������1Mbps 
	Pid_ChassisSpeedInit();
	PidChassisPosInit();
	ZeroCheck_Init();	
	while(1)
	{	
//		Motor_motion_control();
//		//DataScope��
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
		
		//TIM2ch1 ͨ��1-PA0
		if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			ch1=TIM2CH1_CAPTURE_STA&0X3F;		//����Ĵ���
			ch1*=65536;					//���ʱ���ܺ�
			ch1+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			printf("ch1:%d us\r\n",ch1);	//��ӡ�ܵĸߵ�ƽʱ��
 			TIM2CH1_CAPTURE_STA=0;			//������һ�β���
		}
		
		//TIM2ch2 ͨ��2-PA1
		if(TIM2CH2_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			ch2=TIM2CH2_CAPTURE_STA&0X3F;		//����Ĵ���
			ch2*=65536;					//���ʱ���ܺ�
			ch2+=TIM2CH2_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			printf("ch2:%d us\r\n",ch2);	//��ӡ�ܵĸߵ�ƽʱ��
 			TIM2CH2_CAPTURE_STA=0;			//������һ�β���
		}
		
		//TIM2ch3 ͨ��3-PA2
		if(TIM2CH3_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			ch3=TIM2CH3_CAPTURE_STA&0X3F;		//����Ĵ���
			ch3*=65536;					//���ʱ���ܺ�
			ch3+=TIM2CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			printf("ch3:%d us\r\n",ch3);	//��ӡ�ܵĸߵ�ƽʱ��
 			TIM2CH3_CAPTURE_STA=0;			//������һ�β���
		}
		
		//TIM2ch4 ͨ��4-PA3
		if(TIM2CH4_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			ch4=TIM2CH4_CAPTURE_STA&0X3F;		//����Ĵ���
			ch4*=65536;					//���ʱ���ܺ�
			ch4+=TIM2CH4_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			printf("ch4:%d us\r\n",ch4);	//��ӡ�ܵĸߵ�ƽʱ��
 			TIM2CH4_CAPTURE_STA=0;			//������һ�β���
		}
//		//TIM1ch1 ͨ��5
//		if(TIM1CH1_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
//		{
//			ch5=TIM1CH1_CAPTURE_STA&0X3F;		//����Ĵ���
//			ch5*=65536;					//���ʱ���ܺ�
//			ch5+=TIM1CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
//			printf("ch5:%d us\r\n",ch5);	//��ӡ�ܵĸߵ�ƽʱ��
// 			TIM1CH1_CAPTURE_STA=0;			//������һ�β���
//		}
//		//TIM1ch4 ͨ��6
//		if(TIM1CH4_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
//		{
//			ch6=TIM1CH4_CAPTURE_STA&0X3F;		//����Ĵ���
//			ch6*=65536;					//���ʱ���ܺ�
//			ch6+=TIM1CH4_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
//			printf("ch6:%d us\r\n",ch6);	//��ӡ�ܵĸߵ�ƽʱ��
// 			TIM1CH4_CAPTURE_STA=0;			//������һ�β���		
// 		}			
		
		if((ch1>1200 && ch1<1800) && ch2>1900)
			chassis_forward(set_speed);					//ǰ
		else if(ch1>1200 && ch2<1000)
			chassis_back(set_speed);					//��
		else if(ch1<1000 && (ch2>1350 && ch2<1500))
			chassis_left(set_speed);					//����
		else if(ch1>1900 && (ch2>1350 && ch2<1500))
			chassis_right(set_speed);					//����
		else if(ch1<1100 && ch2>1900)
			chassis_leftrota(set_speed);				//����
		else if(ch1>1900 && ch2>1900)	
			chassis_rightrota(set_speed);				//˳��
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
