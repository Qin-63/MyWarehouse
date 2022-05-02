#include "delay.h"

void delay(u16 i)
{
	u8 j;
	while(i--)
		for(j=0;j<123;j++);
}
