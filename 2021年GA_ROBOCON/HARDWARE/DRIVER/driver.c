#include "driver.h"
#include "delay.h"
#include "usart.h"
#include "oled0561.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//´ËÀı³ÌÓĞ²Î¿¼ÂÛÌ³ÍøÓÑÀı³ÌµÄÒ»²¿·Ö(http://www.openedv.com/thread-41832-1-1.html)
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//²½½øµç»úÇı¶¯Æ÷ ²âÊÔ´úÂë			   
//lycreturn@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2016/05/12
//°æ±¾£ºV1.0
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 2009-2019
//All rights reserved	
//********************************************************************************
//ĞŞ¸ÄÈÕÆÚ:2016/05/12
//////////////////////////////////////////////////////////////////////////////////
/********** Çı¶¯Æ÷ ¶Ë¿Ú¶¨Òå **************
//DRIVER_DIR   PC0 
//DRIVER_OE    PC2 
//STEP_PULSE   PC7 (TIM8_CH2,LCD_RW)
******************************************/

u8 rcr_remainder;   //ÖØ¸´¼ÆÊıÓàÊı²¿·Ö
u8 is_rcr_finish=1; //ÖØ¸´¼ÆÊıÆ÷ÊÇ·ñÉèÖÃÍê³É
long rcr_integer;	//ÖØ¸´¼ÆÊıÕûÊı²¿·Ö
long target_pos=0;  //ÓĞ·ûºÅ·½Ïò
long current_pos=0; //ÓĞ·ûºÅ·½Ïò
long current_pos1=0; //ÓĞ·ûºÅ·½Ïò
long current_pos2=0; //ÓĞ·ûºÅ·½Ïò
DIR_Type motor_dir=CW;//Ë³Ê±Õë

/************** Çı¶¯Æ÷¿ØÖÆĞÅºÅÏß³õÊ¼»¯ ****************/
void Driver_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//Ê¹ÄÜPC¶Ë¿ÚÊ±ÖÓ

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2;	//PC0.2 ¶Ë¿ÚÅäÖÃ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO¿ÚËÙ¶ÈÎª50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//¸ù¾İÉè¶¨²ÎÊı³õÊ¼»¯GPIOC
	GPIO_SetBits(GPIOC,GPIO_Pin_0);						 	//PC0Êä³ö¸ß Ë³Ê±Õë·½Ïò  DRIVER_DIR
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);						//PC2Êä³öµÍ Ê¹ÄÜÊä³ö  DRIVER_OE
}

/***********************************************
//TIM8_CH2(PC7) µ¥Âö³åÊä³ö+ÖØ¸´¼ÆÊı¹¦ÄÜ³õÊ¼»¯
//TIM8 Ê±ÖÓÆµÂÊ 72MHz
//arr£º×Ô¶¯ÖØ×°Öµ
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
************************************************/
void TIM8_OPM_RCR_Init(u16 arr,u16 psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //TIM8Ê±ÖÓÊ¹ÄÜ
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  //Ê¹ÄÜGPIOCÍâÉèÊ±ÖÓÊ¹ÄÜ	                                                                     	

  //ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ,Êä³öTIM8 CH2µÄPWMÂö³å²¨ĞÎ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8; //TIM8_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	TIM_ClearITPendingBit(TIM8,TIM_IT_Update);

	TIM_UpdateRequestConfig(TIM8,TIM_UpdateSource_Regular); /********* ÉèÖÃÖ»ÓĞ¼ÆÊıÒç³ö×÷Îª¸üĞÂÖĞ¶Ï ********/
	TIM_SelectOnePulseMode(TIM8,TIM_OPMode_Single);/******* µ¥Âö³åÄ£Ê½ **********/
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³ö2Ê¹ÄÜ
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; /****** ±È½ÏÊä³ö2NÊ§ÄÜ *******/
	TIM_OCInitStructure.TIM_Pulse = arr>>1; //ÉèÖÃ´ı×°Èë²¶»ñ±È½Ï¼Ä´æÆ÷µÄÂö³åÖµ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //¸ù¾İTIM_OCInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2Ô¤×°ÔØÊ¹ÄÜ	 
	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //¸ù¾İTIM_OCInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2Ô¤×°ÔØÊ¹ÄÜ
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_ITConfig(TIM8, TIM_IT_Update ,ENABLE);  //TIM8   Ê¹ÄÜ»òÕßÊ§ÄÜÖ¸¶¨µÄTIMÖĞ¶Ï
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;  //TIM8ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //ÏÈÕ¼ÓÅÏÈ¼¶1¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //´ÓÓÅÏÈ¼¶1¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷
	
	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);  //Çå³ıTIMxµÄÖĞ¶Ï´ı´¦ÀíÎ»:TIM ÖĞ¶ÏÔ´
	TIM_Cmd(TIM8, ENABLE);  //Ê¹ÄÜTIM8									  
}
/******* TIM8¸üĞÂÖĞ¶Ï·şÎñ³ÌĞò *********/
void TIM8_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8,TIM_FLAG_Update)!=RESET)//¸üĞÂÖĞ¶Ï
	{
		TIM_ClearITPendingBit(TIM8,TIM_FLAG_Update);//Çå³ı¸üĞÂÖĞ¶Ï±êÖ¾Î»		
		if(is_rcr_finish==0)//ÖØ¸´¼ÆÊıÆ÷Î´ÉèÖÃÍê³É
		{
			if(rcr_integer!=0) //ÕûÊı²¿·ÖÂö³å»¹Î´·¢ËÍÍê³É
			{
				TIM8->RCR=RCR_VAL;//ÉèÖÃÖØ¸´¼ÆÊıÖµ
				rcr_integer--;//¼õÉÙRCR_VAL+1¸öÂö³å				
			}else if(rcr_remainder!=0)//ÓàÊı²¿·ÖÂö³å ²»Î»0
			{
				TIM8->RCR=rcr_remainder-1;//ÉèÖÃÓàÊı²¿·Ö
				rcr_remainder=0;//ÇåÁã
				is_rcr_finish=1;//ÖØ¸´¼ÆÊıÆ÷ÉèÖÃÍê³É				
			}else goto out;   //rcr_remainder=0£¬Ö±½ÓÍË³ö			 
			TIM_GenerateEvent(TIM8,TIM_EventSource_Update);//²úÉúÒ»¸ö¸üĞÂÊÂ¼ş ÖØĞÂ³õÊ¼»¯¼ÆÊıÆ÷
			TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE Ö÷Êä³öÊ¹ÄÜ	
			TIM_Cmd(TIM8, ENABLE);  //Ê¹ÄÜTIM8			
			if(motor_dir==CW) //Èç¹û·½ÏòÎªË³Ê±Õë   
				current_pos+=(TIM8->RCR+1);//¼ÓÉÏÖØ¸´¼ÆÊıÖµ
			else          //·ñÔò·½ÏòÎªÄæÊ±Õë
				current_pos-=(TIM8->RCR+1);//¼õÈ¥ÖØ¸´¼ÆÊıÖµ			
		}else
		{
out:		is_rcr_finish=1;//ÖØ¸´¼ÆÊıÆ÷ÉèÖÃÍê³É
			TIM_CtrlPWMOutputs(TIM8,DISABLE);	//MOE Ö÷Êä³ö¹Ø±Õ
			TIM_Cmd(TIM8, DISABLE);  //¹Ø±ÕTIM8				
			printf("µ±Ç°Î»ÖÃ=%ld\r\n",current_pos);//´òÓ¡Êä³ö
		}	
	}
}
/***************** Æô¶¯TIM8 *****************/
void TIM8_Startup(u32 frequency,u8 ch)   //Æô¶¯¶¨Ê±Æ÷8
{
	u16 temp_arr=1000000/frequency-1; 
	TIM_SetAutoreload(TIM8,temp_arr);//Éè¶¨×Ô¶¯ÖØ×°Öµ
	
switch(ch){	
	case 1: TIM_CCxCmd(TIM8,TIM_Channel_3,TIM_CCx_Disable);
	        TIM_CCxCmd(TIM8,TIM_Channel_2,TIM_CCx_Enable);
	      	TIM_SetCompare2(TIM8,temp_arr>>1);break; //Æ¥ÅäÖµ2µÈÓÚÖØ×°ÖµÒ»°ë£¬ÊÇÒÔÕ¼¿Õ±ÈÎª50%	
  case 2: TIM_CCxCmd(TIM8,TIM_Channel_2,TIM_CCx_Disable);
	        TIM_CCxCmd(TIM8,TIM_Channel_3,TIM_CCx_Enable);
          TIM_SetCompare3(TIM8,temp_arr>>1);break;}
	TIM_SetCounter(TIM8,0);//¼ÆÊıÆ÷ÇåÁã
	TIM_Cmd(TIM8, ENABLE);  //Ê¹ÄÜTIM8
}
/********************************************
//Ïà¶Ô¶¨Î»º¯Êı 
//num 0¡«2147483647
//frequency: 20Hz~100KHz
//dir: CW(Ë³Ê±Õë·½Ïò)  CCW(ÄæÊ±Õë·½Ïò)
*********************************************/
void Locate_Rle(long num,u32 frequency,DIR_Type dir,u8 ch) //Ïà¶Ô¶¨Î»º¯Êı
{
	if(num<=0) //ÊıÖµĞ¡µÈÓÚ0 ÔòÖ±½Ó·µ»Ø
	{
		printf("\r\nThe num should be greater than zero!!\r\n");
		return;
	}
	if(TIM8->CR1&0x01)//ÉÏÒ»´ÎÂö³å»¹Î´·¢ËÍÍê³É  Ö±½Ó·µ»Ø
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//Âö³åÆµÂÊ²»ÔÚ·¶Î§ÄÚ Ö±½Ó·µ»Ø
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	motor_dir=dir;//µÃµ½·½Ïò	
	DRIVER_DIR=motor_dir;//ÉèÖÃ·½Ïò
	//¸³Öµµ±Ç°Î»ÖÃ
	switch(ch){case 1:current_pos=current_pos1;break;
		         case 2:current_pos=current_pos2;break;}
	
	if(motor_dir==CW)//Ë³Ê±Õë
		target_pos=current_pos+num;//Ä¿±êÎ»ÖÃ
	else if(motor_dir==CCW)//ÄæÊ±Õë
		target_pos=current_pos-num;//Ä¿±êÎ»ÖÃ
	
	//±£Áôµ±Ç°Î»ÖÃÃ
	switch(ch){case 1:current_pos1=target_pos;break;
		         case 2:current_pos2=target_pos;break;}
	
	rcr_integer=num/(RCR_VAL+1);//ÖØ¸´¼ÆÊıÕûÊı²¿·Ö
	rcr_remainder=num%(RCR_VAL+1);//ÖØ¸´¼ÆÊıÓàÊı²¿·Ö
	is_rcr_finish=0;//ÖØ¸´¼ÆÊıÆ÷Î´ÉèÖÃÍê³É
	TIM8_Startup(frequency,ch);//¿ªÆôTIM8
}
/********************************************
//¾ø¶Ô¶¨Î»º¯Êı 
//num   -2147483648¡«2147483647
//frequency: 20Hz~100KHz
*********************************************/
void Locate_Abs(long num,u32 frequency,u8 ch)//¾ø¶Ô¶¨Î»º¯Êı
{
	if(TIM8->CR1&0x01)//ÉÏÒ»´ÎÂö³å»¹Î´·¢ËÍÍê³É Ö±½Ó·µ»Ø
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//Âö³åÆµÂÊ²»ÔÚ·¶Î§ÄÚ Ö±½Ó·µ»Ø
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	target_pos=num;//ÉèÖÃÄ¿±êÎ»ÖÃ
	
	//µ±Ç°Î»ÖÃ
	switch(ch){case 1:current_pos=current_pos1;current_pos1=num;break;
	           case 2:current_pos=current_pos2;current_pos2=num;break;}
	
	if(target_pos!=current_pos)//Ä¿±êºÍµ±Ç°Î»ÖÃ²»Í¬
	{
		if(target_pos>current_pos)
			motor_dir=CW;//Ë³Ê±Õë
		else
			motor_dir=CCW;//ÄæÊ±Õë
		DRIVER_DIR=motor_dir;//ÉèÖÃ·½Ïò
		
		rcr_integer=abs(target_pos-current_pos)/(RCR_VAL+1);//ÖØ¸´¼ÆÊıÕûÊı²¿·Ö
		rcr_remainder=abs(target_pos-current_pos)%(RCR_VAL+1);//ÖØ¸´¼ÆÊıÓàÊı²¿·Ö
		is_rcr_finish=0;//ÖØ¸´¼ÆÊıÆ÷Î´ÉèÖÃÍê³É
		TIM8_Startup(frequency,ch);//¿ªÆôTIM8
	}
}



//void target(long num)
//{   //num=0;
//	  if(num<0)
//		{OLED_DISPLAY_8x16(0,9*8,'-');
//		  num=-num;}
//			else OLED_DISPLAY_8x16(0,9*8,' ');
//	  OLED_DISPLAY_8x16(0,10*8,num/10000+0x30);
//		OLED_DISPLAY_8x16(0,11*8,num/1000%10+0x30);
//		OLED_DISPLAY_8x16(0,12*8,num/100%10+0x30);	
//		OLED_DISPLAY_8x16(0,13*8,num/10%10+0x30);
//   	OLED_DISPLAY_8x16(0,14*8,num%10+0x30); 
//}

