#include "zidong.h"
#include "usart.h"
#include "delay.h"
#include "oled0561.h"
char cc[3]={0x69,0x53,0x4d};      //�����൥�β�����ָ��iSM

void ceju(void)
{   int t;
    for(t=0;t<3;t++)
        {
				while((USART3->SR&0X40)==0);   //�ȴ����ͽ���
				USART3->DR=cc[t];   //��������
		    }
			  while((USART3->SR&0X40)==0);//�ȴ����ͽ���
			  USART3->DR=0x0d;
			  while((USART3->SR&0X40)==0);//�ȴ����ͽ���
			  USART3->DR=0x0a;
			  while((USART3->SR&0X40)==0);//�ȴ����ͽ���	
			  delay_ms(1000);
			//������ת�����ָ���Ƕ�
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
		{ if(USART3_RX_BUF[3]==0x2E){    //��ʾֻҪ10�����µ�ֵ
			distance=(USART3_RX_BUF[2]-0x30)*100;
			distance=(USART3_RX_BUF[4]-0.30)*10+distance;
			distance=(USART3_RX_BUF[5]-0x30)+distance;}  //USART3_RX_BUF[6];
			if(distance>0){return distance;}			
		}
   return 0;		
}

void jiaozhunjl(int a){    //aֵΪ������Ҫ��ͣ��
	char t=1;
	int dis;
	while(t){
		ceju();
		dis=jl_change();
		if(dis!=0)
		dis=dis-a;
if(dis>2){    //Զ��
	//ǰ��     ���ʱ����Ҫ����
	
}
if(dis<-2){   //����
  //����     ���ʱ����Ҫ����
	 
}
if(dis<2&&dis>-2){//�ﵽ����������   ����ѭ��
	t=0;   //t=0  �ͽ����˾���У׼
}
	}	
}

