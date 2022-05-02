#include "zidong.h"
#include "usart.h"
#include "delay.h"
#include "oled0561.h"
char cc[3]={0x69,0x53,0x4d};      //激光测距单次测量的指令iSM

void ceju(void)
{   int t;
    for(t=0;t<3;t++)
        {
				while((USART3->SR&0X40)==0);   //等待发送结束
				USART3->DR=cc[t];   //发送数据
		    }
			  while((USART3->SR&0X40)==0);//等待发送结束
			  USART3->DR=0x0d;
			  while((USART3->SR&0X40)==0);//等待发送结束
			  USART3->DR=0x0a;
			  while((USART3->SR&0X40)==0);//等待发送结束	
			  delay_ms(1000);
			//调整旋转舵机到指定角度
			if(USART3_RX_STA){
			if((USART3_RX_BUF[0]==0x44)&(USART3_RX_BUF[1]==0x3d))
			{ 
				OLED_DISPLAY_8x16(2,9*8,USART3_RX_BUF[2]);
				OLED_DISPLAY_8x16(2,10*8,USART3_RX_BUF[4]);
				OLED_DISPLAY_8x16(2,11*8,USART3_RX_BUF[5]);
        OLED_DISPLAY_8x16(2,12*8,'.');					
				OLED_DISPLAY_8x16(2,13*8,USART3_RX_BUF[6]); 
			  USART3_RX_STA=0;
			}}
}

int	jl_change(void){
	int distance=0;
	if((USART3_RX_BUF[0]==0x44)&(USART3_RX_BUF[1]==0x3d))
		{ if(USART3_RX_BUF[3]==0x2E){    //表示只要10米以下的值
			distance=(USART3_RX_BUF[2]-0x30)*100;
			distance=(USART3_RX_BUF[4]-0.30)*10+distance;
			distance=(USART3_RX_BUF[5]-0x30)+distance;}  //USART3_RX_BUF[6];
			if(distance>0){return distance;}			
		}
   return 0;		
}

void jiaozhunjl(int a){    //a值为我们想要车停在
	char t=1;
	int dis;
	while(t){
		ceju();
		dis=jl_change();
		if(dis!=0)
		dis=dis-a;
if(dis>2){    //远了
	//前进     这个时间需要调试
	
}
if(dis<-2){   //近了
  //后退     这个时间需要调试
	 
}
if(dis<2&&dis>-2){//达到允许的误差内   跳出循环
	t=0;   //t=0  就结束了距离校准
}
	}	
}

