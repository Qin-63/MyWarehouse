#ifndef __MAIN_H
#define __MAIN_H

#include <stm32f10x.h>

//Hardware
#include "sys.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"	 
#include "can.h" 
#include "motor.h"
#include "pid.h"
#include "tim3.h"
#include "DataScope_DP.h"
#include "ZeroCheck.h"
#include "timer.h"
#include "timer1.h"


#define LIMIT_MAX_MIN(x, max, min)	(((x) <= (min)) ? (min):(((x) >= (max)) ? (max) : (x)))
#define ABS(x) ((x)>0? (x):(-(x))) 

#endif
