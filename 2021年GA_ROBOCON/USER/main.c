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
//char cc[3]={0x69,0x53,0x4d};      //激光测距单次测量的指令iSM
int speed=400;
//void ceju(void)
//{   int t;
//    for(t=0;t<3;t++)
//        {
//			   while((USART3->SR&0X40)==0);   //等待发送结束
//			   USART3->DR=cc[t];   //发送数据
//		    }
//	  while((USART3->SR&0X40)==0);//等待发送结束
//	  USART3->DR=0x0d;
//	  while((USART3->SR&0X40)==0);//等待发送结束
//	  USART3->DR=0x0a;
//	  while((USART3->SR&0X40)==0);//等待发送结束	
//	  delay_ms(1000);
//			//调整旋转舵机到指定角度
//	if(USART3_RX_STA){
//	if((USART3_RX_BUF[0]==0x44)&(USART3_RX_BUF[1]==0x3d))
//	{ 
//	//发送给手机上的上位机，显示距离
//		 while((USART1->SR&0X40)==0);//等待发送结束
//		  USART1->DR=USART3_RX_BUF[2];
//		  while((USART1->SR&0X40)==0);//等待发送结束
//			 USART1->DR=USART3_RX_BUF[4];
//		  while((USART1->SR&0X40)==0);//等待发送结束
//			 USART1->DR=USART3_RX_BUF[5];
//		  while((USART1->SR&0X40)==0);//等待发送结束
//			 USART1->DR=USART3_RX_BUF[6];
//		  while((USART1->SR&0X40)==0);//等待发送结束				
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
	 delay_init();	    	 //延时函数初始化	
	 delay_ms(500); //上电时等待其他器件就绪
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
   //串口初始化	 
	 USART1_Init(9600);
	 USART3_Init(38400);	 
//    KEY_Init(); //按键初始化
	 arm_init(); //机械臂初始化的状态
	 angle_change();  //发送数据给舵机模块   串口1发送 
	 car_en_init();  //车轮使能端初始化	 
	 //步进电机 初始化 后面这两行不要去改动
	 Driver_Init();                  //驱动器初始化

     EXTIX_Init();	 
     I2C_Configuration();//I2C初始化
	 OLED0561_Init(); //OLED初始化 
	 OLED_DISPLAY_8x16_BUFFER(0,"    GA Studio"); //显示字符串

//		while((USART3->SR&0X40)==0);	  
//		USART3->DR=0x33;
//		while((USART3->SR&0X40)==0);//等待发送结束
//		USART3->DR=0x34;
//		while((USART3->SR&0X40)==0);//等待发送结束
//		OLED_DISPLAY_8x16(2,9*8,USART3_RX_BUF[2]);
//		OLED_DISPLAY_8x16(2,10*8,USART3_RX_BUF[4]);
//		OLED_DISPLAY_8x16(2,11*8,USART3_RX_BUF[5]);
//		OLED_DISPLAY_8x16(2,12*8,'.');					
//		OLED_DISPLAY_8x16(2,13*8,USART3_RX_BUF[6]); 
	 TIM8_OPM_RCR_Init(999,72-1);    //1MHz计数频率  单脉冲+重复计数模式		
	 //车轮控制+继电器4个（PC9 10 11 12）控制端口初始化 
     TIM3_PWM_Init(999,9); 
     //控制车轮的代码   
	 TIM_SetCompare3(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	 TIM_SetCompare2(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	 TIM_SetCompare1(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	 TIM_SetCompare4(TIM3,0);        //改变比较值TIM3->CCR2达到调节占空比的效果（1500为0度）
	 
	 //继电器的初始状态
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_12);
	 // car_advance(200);
	 while(1)
	 { 
		switch(key)   //key=蓝牙发送，串口1接收的值。
		{	//车轮的控制			 
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
			//捡箭的操作·
			case 'e':  //1    准备捡箭
              arm_1();angle_change();key=0;break;
//			case 'f':  //2    夹箭
//				arm_2(); angle_change();key=0;break;
//			case 'g':  //3    抬起
//		        arm_3();angle_change();key=0;break;
//			case 'h':  //4		准备放箭	
//		        arm_4();angle_change();key=0;break;
//			case 'i':  //5		放箭	
//		        arm_5();angle_change();key=0;break;
			
			//一键合成捡箭
			case 'f':jianjian();key=0;break;
			
			
			//炮管升降操作
			case 'j':  //6    顺时针  上升
                 Locate_Rle(100,1000,CW,1); //按下KEY0，以500Hz的频率  顺时针发200脉冲
				 xxx=xxx+1;
				 OLED_DISPLAY_8x16(4,10*8,xxx/100+0x30);
				 OLED_DISPLAY_8x16(4,11*8,xxx/10%10+0x30);
				 OLED_DISPLAY_8x16(4,12*8,xxx%10+0x30); 			
				 key=0;break;
			case 'k':  //7    逆时针  下降
				 Locate_Rle(100,1000,CCW,1);//按下KEY1，以500Hz的频率 逆时针发400脉冲
				 xxx=xxx-1;
				 OLED_DISPLAY_8x16(4,10*8,xxx/100+0x30);
				 OLED_DISPLAY_8x16(4,11*8,xxx/10%10+0x30);
				 OLED_DISPLAY_8x16(4,12*8,xxx%10+0x30);			
		         key=0;break;
			case 'l':  //8       回零点
                 Locate_Abs(0,1000,1);//按下WKUP
				 xxx=0;
				 OLED_DISPLAY_8x16(4,10*8,xxx/100+0x30);
				 OLED_DISPLAY_8x16(4,11*8,xxx/10%10+0x30);
				 OLED_DISPLAY_8x16(4,12*8,xxx%10+0x30);        			
				 key=0;break;
			
			//炮管发射的操作
			case 'm':  //9			 发射
			     GPIO_SetBits(GPIOC,GPIO_Pin_11);
			     delay_ms(2000);
			     GPIO_ResetBits(GPIOC,GPIO_Pin_11);
				 key=0;break;
			case 'n':  //10			 上膛
			     GPIO_SetBits(GPIOC,GPIO_Pin_12);
			     delay_ms(1500);
			     GPIO_ResetBits(GPIOC,GPIO_Pin_12); 
				 key=0;break;
			
            //干扰操作			
     	    case 'o': 
				 //Locate_Rle(200,1000,CW,2); //按下KEY0，以500Hz的频率  顺时针发200脉冲
                 GPIO_SetBits(GPIOC,GPIO_Pin_9);
                 GPIO_SetBits(GPIOC,GPIO_Pin_10);			
				 key=0;break;	
			case 'p': 
				 //Locate_Rle(100,1000,CCW,2);//按下KEY1，以500Hz的频率 逆时针发400脉冲
                 GPIO_ResetBits(GPIOC,GPIO_Pin_9); 
                 GPIO_ResetBits(GPIOC,GPIO_Pin_10); 			
				 key=0;break;	
			case 'q': 
			     //Locate_Abs(0,1000,2);//按下WKUP，
			     
			     key=0;break;
            //测距   单次测量
			case 'r':  //发送测距指令   得到距离  并用oled显示
                 ceju();
			     key=0;break;
		} 	
	}
}	


//外部中断3服务程序    陀螺仪发现角度小了   上升   PB4
//void EXTI3_IRQHandler(void)
//{
//	delay_ms(10);//消抖
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==0)	 //按键KEY1
//	{				 
////		LED1=!LED1;
//	Locate_Rle(200,1000,CW,1);
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
//}


////陀螺仪发现角度大了    下降   PB4
//void EXTI4_IRQHandler(void)
//{
//	delay_ms(10);//消抖
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)	 //按键KEY0
//	{
////		LED0=!LED0;
////		LED1=!LED1;
//  Locate_Rle(100,1000,CCW,1);
//	
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
//}


//步进电机驱动示例
//		if(keyval==WKUP_PRES)
//		{
//			Locate_Abs(0,500);//按下WKUP，回零点
//		}else if(keyval==KEY0_PRES)
//		{
//			Locate_Rle(200,500,CW); //按下KEY0，以500Hz的频率  顺时针发200脉冲
//		}else if(keyval==KEY1_PRES)
//		{
//			Locate_Rle(400,500,CCW);//按下KEY1，以500Hz的频率  逆时针发400脉冲
//		}
//    /*发送命令使，舵机转动*/	
//			for(t=0;t<5;t++)
//			{ 
//				while((USART1->SR&0X40)==0);//等待发送结束
//				USART1->DR=buf[t];          //发送数据    数据在DR寄存器里可以直接发送数据   printf函数也可以发送数据
//			}
//			while((USART1->SR&0X40)==0);//等待发送结束
//			printf("\r\n\r\n"); //插入换行
//			delay_ms(3000);

