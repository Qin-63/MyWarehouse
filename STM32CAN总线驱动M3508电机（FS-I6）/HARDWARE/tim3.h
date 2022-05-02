#ifndef __TIM3_H
#define __TIM3_H
#include "sys.h" 

extern int16_t motor_cur_out[4];
extern float zerocheck_out,zerocheck_last_out,real_pos;

extern void TIM3_Int_Init(u16 arr,u16 psc);
 
#endif
