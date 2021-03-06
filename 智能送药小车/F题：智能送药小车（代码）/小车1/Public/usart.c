#include "usart.h"
#include <control.h>	
#include "motor.h"
#include "systick.h"
#include "motion.h"

s8 kxie=0;
u8 k210_t=0;
u8 k210_r=0;
u8 k210_mubiao=0;
u8 ditu=0;

int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(UART4,(u8)ch);	
	while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
	return ch;
}


void Usart1_Init(u32 bound)
{
    /* GPIO端口设置 */
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

	//USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}


void Usart3_Init(u32 bound)
{
    /* GPIO端口设置 */
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* 初始化串口输入IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOB,&GPIO_InitStructure); /* 初始化GPIO */
	

	//USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART3, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}


void Uart4_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);  /* 初始化串口输入IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOC,&GPIO_InitStructure); /* 初始化GPIO */
	

	//USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(UART4, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(UART4, ENABLE);  //使能串口1 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
		
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}


void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 x;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)	//接收中断
	{
		kxie=USART_ReceiveData(USART1);	//读取接收到的信息
		//printf("%d\r\n",kxie);
		
		//USART_SendData(USART1,x);	//向串口1发送数据
		//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
	USART_ClearFlag(USART1,USART_FLAG_TC);	//清理串口数据 ，，，
}

void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	u8 x;
	static u8 i=0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)	//接收中断
	{
		x=USART_ReceiveData(USART3);	//读取接收到的信息
		//printf("%d\r\n",x);
		if(x<9 && i<5)
		{
			++i;
			k210_mubiao=x;
		}
		else if(x>9)
		{
			k210_r=x;
		}
	
		//USART_SendData(USART1,x);	//向串口1发送数据
		//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
	USART_ClearFlag(USART3,USART_FLAG_TC);	//清理串口数据 ，，，
}


void UART4_IRQHandler(void)                	//串口1中断服务程序
{
	u8 x;
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)	//接收中断
	{
		x=USART_ReceiveData(UART4);	//读取接收到的信息
		//printf("%d\r\n",kxie);
		
		//Control(x);
//		USART_SendData(USART3,x);	//向串口1发送数据
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
	USART_ClearFlag(UART4,USART_FLAG_TC);	//清理串口数据 ，，，
}



void Usart4fa_1()
{
	u8 i=0;
	
	for(i=0;i<10;i++)
	{
		USART_SendData(UART4,1);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
}

void Usart4fa_2()
{
	u8 i=0;
	
	for(i=0;i<10;i++)
	{
		USART_SendData(UART4,2);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
}


void Usart4fa_3()
{
	u8 i=0;
	
	for(i=0;i<10;i++)
	{
		USART_SendData(UART4,3);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
}


void Usart4fa_4()
{
	u8 i=0;
	
	for(i=0;i<10;i++)
	{
		USART_SendData(UART4,4);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
}

void Usart4fa_9()
{
	u8 i=0;
	
	for(i=0;i<10;i++)
	{
		USART_SendData(UART4,9);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);	//等待数据发送结束
	}
}


void Usart4_Ditu(u8 x)
{
	u8 i=0;
	while(ditu==1 && i<10)	
	switch(x)
	{
		case(0):   printf("page 0\xff\xff\xff");  ++i;  break;
		case(1):   printf("page 1\xff\xff\xff");  ++i;  break;
		case(2):   printf("page 2\xff\xff\xff");  ++i;  break;
		case(3):   printf("page 3\xff\xff\xff");  ++i;  break;
		case(4):   printf("page 4\xff\xff\xff");  ++i;  break;
		case(5):   printf("page 5\xff\xff\xff");  ++i;  break;
		case(6):   printf("page 6\xff\xff\xff");  ++i;  break;
		case(7):   printf("page 7\xff\xff\xff");  ++i;  break;
		case(8):   printf("page 8\xff\xff\xff");  ++i;  break;
		case(9):   printf("page 9\xff\xff\xff");  ++i;  break;
		case(10):  printf("page 10\xff\xff\xff"); ++i;  break;
	}
}


