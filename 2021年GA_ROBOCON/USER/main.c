#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "arm.h"
#include "wheel.h"
#include "driver.h"
#include "oled0561.h"
#include "i2c.h"
#include "exti.h"
#include "zidong.h"
u8 run_sta=0;
u8 xxx=0;
u8 t;
//char cc[3]={0x69,0x53,0x4d};      //�����൥�β�����ָ��iSM
int speed=400;
//void ceju(void)
//{   int t;
//    for(t=0;t<3;t++)
//        {
//			   while((USART3->SR&0X40)==0);   //�ȴ����ͽ���
//			   USART3->DR=cc[t];   //��������
//		    }
//	  while((USART3->SR&0X40)==0);//�ȴ����ͽ���
//	  USART3->DR=0x0d;
//	  while((USART3->SR&0X40)==0);//�ȴ����ͽ���
//	  USART3->DR=0x0a;
//	  while((USART3->SR&0X40)==0);//�ȴ����ͽ���	
//	  delay_ms(1000);
//			//������ת�����ָ���Ƕ�
//	if(USART3_RX_STA){
//	if((USART3_RX_BUF[0]==0x44)&(USART3_RX_BUF[1]==0x3d))
//	{ 
//	//���͸��ֻ��ϵ���λ������ʾ����
//		 while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//		  USART1->DR=USART3_RX_BUF[2];
//		  while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			 USART1->DR=USART3_RX_BUF[4];
//		  while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			 USART1->DR=USART3_RX_BUF[5];
//		  while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			 USART1->DR=USART3_RX_BUF[6];
//		  while((USART1->SR&0X40)==0);//�ȴ����ͽ���				
//		OLED_DISPLAY_8x16(2,9*8,USART3_RX_BUF[2]);
//		OLED_DISPLAY_8x16(2,10*8,USART3_RX_BUF[4]);
//		OLED_DISPLAY_8x16(2,11*8,USART3_RX_BUF[5]);
//		OLED_DISPLAY_8x16(2,12*8,'.');					
//		OLED_DISPLAY_8x16(2,13*8,USART3_RX_BUF[6]); 
//		USART3_RX_STA=0;
//    }}
//}

void jianjian(void){
	arm_2();angle_change();delay_ms(600);
	arm_3();angle_change();delay_ms(600);
	arm_4();angle_change();delay_ms(600);
	arm_5();angle_change();
	
}
void run_mode(void)
{
	switch(run_sta)
	{
		case 1:  brake();break;
		case 2:  car_advance(speed);break;
		case 3:  car_back(speed);break;
		case 4:  car_left(speed);break;
		case 5:  car_right(speed);break;
		case 6:  car_left_rotation(speed);break;
		case 7:  car_right_rotation(speed);break;
		case 8:  car_left_front(speed);break;
		case 9:  car_right_front(speed);break;
		case 10: car_left_back(speed);break;
    case 11: car_right_back(speed);break;
		default: break;
	}
}
 int main(void)
 {	
	int sta_speed=650;	 
	 delay_init();	    	 //��ʱ������ʼ��	
	 delay_ms(500); //�ϵ�ʱ�ȴ�������������
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
   //���ڳ�ʼ��	 
	 USART1_Init(9600);
	 USART3_Init(38400);	 
//    KEY_Init(); //������ʼ��
	 arm_init(); //��е�۳�ʼ����״̬
	 angle_change();  //�������ݸ����ģ��   ����1���� 
	 car_en_init();  //����ʹ�ܶ˳�ʼ��	 
	 //������� ��ʼ�� ���������в�Ҫȥ�Ķ�
	 Driver_Init();                  //��������ʼ��

     EXTIX_Init();	 
     I2C_Configuration();//I2C��ʼ��
	 OLED0561_Init(); //OLED��ʼ�� 
	 OLED_DISPLAY_8x16_BUFFER(0,"    GA Studio"); //��ʾ�ַ���

//		while((USART3->SR&0X40)==0);	  
//		USART3->DR=0x33;
//		while((USART3->SR&0X40)==0);//�ȴ����ͽ���
//		USART3->DR=0x34;
//		while((USART3->SR&0X40)==0);//�ȴ����ͽ���
//		OLED_DISPLAY_8x16(2,9*8,USART3_RX_BUF[2]);
//		OLED_DISPLAY_8x16(2,10*8,USART3_RX_BUF[4]);
//		OLED_DISPLAY_8x16(2,11*8,USART3_RX_BUF[5]);
//		OLED_DISPLAY_8x16(2,12*8,'.');					
//		OLED_DISPLAY_8x16(2,13*8,USART3_RX_BUF[6]); 
	 TIM8_OPM_RCR_Init(999,72-1);    //1MHz����Ƶ��  ������+�ظ�����ģʽ		
	 //���ֿ���+�̵���4����PC9 10 11 12�����ƶ˿ڳ�ʼ�� 
     TIM3_PWM_Init(999,9); 
     //���Ƴ��ֵĴ���   
	 TIM_SetCompare3(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	 TIM_SetCompare2(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	 TIM_SetCompare1(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	 TIM_SetCompare4(TIM3,0);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч����1500Ϊ0�ȣ�
	 
	 //�̵����ĳ�ʼ״̬
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_12);
	 // car_advance(200);
	 while(1)
	 { 
		switch(key)   //key=�������ͣ�����1���յ�ֵ��
		{	//���ֵĿ���			 
			case '1' : brake();run_sta=1;key=0;break;
			case '2': car_advance(speed);run_sta=2;key=0;break;
			case '3': car_back(speed);run_sta=3;key=0;break;
			
			case '4': car_left(sta_speed);run_sta=4;key=0;break;
			case '5': car_right(sta_speed);run_sta=5;key=0;break;
			case '6': car_left_rotation(speed);run_sta=6;key=0;break;
			case '7': car_right_rotation(speed);run_sta=7;key=0;break;
			
			case '8': car_left_front(900);run_sta=8;key=0;break;  //
			case '9': car_right_front(900);run_sta=9;key=0;break;
			case 'a': car_left_back(900);run_sta=10;key=0;break;  
			case 'b': car_right_back(900);run_sta=11;key=0;break;
			
			case 'c': speed+=20; if(speed>750)  speed=750; run_mode(); key=0;break;
			case 'd': speed-=20; if(speed<300)  speed=300; run_mode(); key=0;break;
			//����Ĳ�����
			case 'e':  //1    ׼�����
              arm_1();angle_change();key=0;break;
//			case 'f':  //2    �м�
//				arm_2(); angle_change();key=0;break;
//			case 'g':  //3    ̧��
//		        arm_3();angle_change();key=0;break;
//			case 'h':  //4		׼���ż�	
//		        arm_4();angle_change();key=0;break;
//			case 'i':  //5		�ż�	
//		        arm_5();angle_change();key=0;break;
			
			//һ���ϳɼ��
			case 'f':jianjian();key=0;break;
			
			
			//�ڹ���������
			case 'j':  //6    ˳ʱ��  ����
                 Locate_Rle(100,1000,CW,1); //����KEY0����500Hz��Ƶ��  ˳ʱ�뷢200����
				 xxx=xxx+1;
				 OLED_DISPLAY_8x16(4,10*8,xxx/100+0x30);
				 OLED_DISPLAY_8x16(4,11*8,xxx/10%10+0x30);
				 OLED_DISPLAY_8x16(4,12*8,xxx%10+0x30); 			
				 key=0;break;
			case 'k':  //7    ��ʱ��  �½�
				 Locate_Rle(100,1000,CCW,1);//����KEY1����500Hz��Ƶ�� ��ʱ�뷢400����
				 xxx=xxx-1;
				 OLED_DISPLAY_8x16(4,10*8,xxx/100+0x30);
				 OLED_DISPLAY_8x16(4,11*8,xxx/10%10+0x30);
				 OLED_DISPLAY_8x16(4,12*8,xxx%10+0x30);			
		         key=0;break;
			case 'l':  //8       �����
                 Locate_Abs(0,1000,1);//����WKUP
				 xxx=0;
				 OLED_DISPLAY_8x16(4,10*8,xxx/100+0x30);
				 OLED_DISPLAY_8x16(4,11*8,xxx/10%10+0x30);
				 OLED_DISPLAY_8x16(4,12*8,xxx%10+0x30);        			
				 key=0;break;
			
			//�ڹܷ���Ĳ���
			case 'm':  //9			 ����
			     GPIO_SetBits(GPIOC,GPIO_Pin_11);
			     delay_ms(2000);
			     GPIO_ResetBits(GPIOC,GPIO_Pin_11);
				 key=0;break;
			case 'n':  //10			 ����
			     GPIO_SetBits(GPIOC,GPIO_Pin_12);
			     delay_ms(1500);
			     GPIO_ResetBits(GPIOC,GPIO_Pin_12); 
				 key=0;break;
			
            //���Ų���			
     	    case 'o': 
				 //Locate_Rle(200,1000,CW,2); //����KEY0����500Hz��Ƶ��  ˳ʱ�뷢200����
                 GPIO_SetBits(GPIOC,GPIO_Pin_9);
                 GPIO_SetBits(GPIOC,GPIO_Pin_10);			
				 key=0;break;	
			case 'p': 
				 //Locate_Rle(100,1000,CCW,2);//����KEY1����500Hz��Ƶ�� ��ʱ�뷢400����
                 GPIO_ResetBits(GPIOC,GPIO_Pin_9); 
                 GPIO_ResetBits(GPIOC,GPIO_Pin_10); 			
				 key=0;break;	
			case 'q': 
			     //Locate_Abs(0,1000,2);//����WKUP��
			     
			     key=0;break;
            //���   ���β���
			case 'r':  //���Ͳ��ָ��   �õ�����  ����oled��ʾ
                 ceju();
			     key=0;break;
		} 	
	}
}	


//�ⲿ�ж�3�������    �����Ƿ��ֽǶ�С��   ����   PB4
//void EXTI3_IRQHandler(void)
//{
//	delay_ms(10);//����
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==0)	 //����KEY1
//	{				 
////		LED1=!LED1;
//	Locate_Rle(200,1000,CW,1);
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
//}


////�����Ƿ��ֽǶȴ���    �½�   PB4
//void EXTI4_IRQHandler(void)
//{
//	delay_ms(10);//����
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)	 //����KEY0
//	{
////		LED0=!LED0;
////		LED1=!LED1;
//  Locate_Rle(100,1000,CCW,1);
//	
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
//}


//�����������ʾ��
//		if(keyval==WKUP_PRES)
//		{
//			Locate_Abs(0,500);//����WKUP�������
//		}else if(keyval==KEY0_PRES)
//		{
//			Locate_Rle(200,500,CW); //����KEY0����500Hz��Ƶ��  ˳ʱ�뷢200����
//		}else if(keyval==KEY1_PRES)
//		{
//			Locate_Rle(400,500,CCW);//����KEY1����500Hz��Ƶ��  ��ʱ�뷢400����
//		}
//    /*��������ʹ�����ת��*/	
//			for(t=0;t<5;t++)
//			{ 
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//				USART1->DR=buf[t];          //��������    ������DR�Ĵ��������ֱ�ӷ�������   printf����Ҳ���Է�������
//			}
//			while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			printf("\r\n\r\n"); //���뻻��
//			delay_ms(3000);

