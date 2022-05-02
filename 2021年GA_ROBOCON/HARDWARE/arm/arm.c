#include "arm.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
//机械臂转动一定角度的数组
//ff + CMD + 0-15 + dataL + dataH 
//dataL=data&0xff  dataH=data>>8
u16 angle1=1500;     //PA6（TIM3-CH1）  
u16 angle2=1500;     //PA7（TIM3-CH2） 4500-7420            
u16 angle3=1500;     //PA0（TIM2-CH1） up down  up down
u16 angle4=500;      //PA1（TIM2-CH2） up up  down down
u16 angle5=1500;     //PB0（TIM3-CH3） 4500是平行    7500是抓东西准备
u16 angle6=466;      //PB1（TIM3-CH4） 400~3460
u8 time=100;
             //包头、指令、通道、低字节、高字节
u8 buf[6][5]={{0xff,0x02,0x00,0xdc,0x05},
              {0xff,0x02,0x01,0xdc,0x05},
              {0xff,0x02,0x02,0xdc,0x05},
              {0xff,0x02,0x03,0xdc,0x05},
              {0xff,0x02,0x04,0xdc,0x05},
              {0xff,0x02,0x05,0xdc,0x05}};

							
u16 angledata[6]={1500,1500,1500,500,1500,466};


void angle_change(void)  //角度转换 + 串口输出
{ u8 i,t;
	for(i=0;i<6;i++)  //角度放进数组
	{ 
		buf[i][3]=angledata[i]&0xff;
		buf[i][4]=angledata[i]>>8;
	}
	
	for(i=0;i<6;i++) //发送六个角度
	{
		for(t=0;t<5;t++) //驱动一个舵机
			{ 
				while((USART1->SR&0X40)==0);//等待发送结束
				USART1->DR=buf[i][t];          //发送数据    数据在DR寄存器里可以直接发送数据   printf函数也可以发送数据
			  delay_ms(time);
			}
			while((USART1->SR&0X40)==0);//等待发送结束
			USART1->DR=0x0d;
			while((USART1->SR&0X40)==0);//等待发送结束
			USART1->DR=0x0a;
			while((USART1->SR&0X40)==0);//等待发送结束
			delay_ms(300);
	}
	
}


//数字，只需修改+前面的数字+
void arm_init(void)	//东西夹住了   90 90 90 90 90 36
{
	angledata[0]=(int)((float)2000/180*90+500);
	angledata[1]=(int)((float)2000/180*90+500);
	angledata[2]=(int)((float)2000/180*90+500);
	angledata[3]=(int)((float)2000/180*90+500);
	angledata[4]=(int)((float)2000/180*90+500);
	angledata[5]=(int)((float)2000/180*90+500);

}


void arm_1(void) //准备放   90 180 5 49 180 75
{
	angledata[0]=(int)((float)2000/180*90+500);
	angledata[1]=(int)((float)2000/180*180+500);
	angledata[2]=(int)((float)2000/180*5+500);
	angledata[3]=(int)((float)2000/180*49+500);
	angledata[4]=(int)((float)2000/180*180+500);
	angledata[5]=(int)((float)2000/180*75+500);
	
}


void arm_2(void) //准备放   90 180 5 49 180 164
{
	angledata[0]=(int)((float)2000/180*90+500);
	angledata[1]=(int)((float)2000/180*180+500);
	angledata[2]=(int)((float)2000/180*5+500);
	angledata[3]=(int)((float)2000/180*49+500);
	angledata[4]=(int)((float)2000/180*180+500);
	angledata[5]=(int)((float)2000/180*164+500);
	
}
void arm_3(void) //准备放   90 119 95 25 180 164
	//90 119 95 25 180 164
{
	angledata[0]=(int)((float)2000/180*90+500);
	angledata[1]=(int)((float)2000/180*119+500);
	angledata[2]=(int)((float)2000/180*95+500);
	angledata[3]=(int)((float)2000/180*25+500);
	angledata[4]=(int)((float)2000/180*180+500);
	angledata[5]=(int)((float)2000/180*164+500);
	
}


void arm_4(void) //放开   90 119 95 25 90 164
{
	angledata[0]=(int)((float)2000/180*90+500);
	angledata[1]=(int)((float)2000/180*119+500);
	angledata[2]=(int)((float)2000/180*95+500);
	angledata[3]=(int)((float)2000/180*25+500);
	angledata[4]=(int)((float)2000/180*90+500);
	angledata[5]=(int)((float)2000/180*164+500);
}


void arm_5(void) //准备拿起   90 119 95 25 90 75
{
	angledata[0]=(int)((float)2000/180*90+500);
	angledata[1]=(int)((float)2000/180*119+500);
	angledata[2]=(int)((float)2000/180*95+500);
	angledata[3]=(int)((float)2000/180*25+500);
	angledata[4]=(int)((float)2000/180*90+500);
	angledata[5]=(int)((float)2000/180*75+500);
}

