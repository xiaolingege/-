#ifndef _DATA_TYPE_H
#define _DATA_TYPE_H

#include "stm32f10x.h"

typedef  enum _BOOL
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;

typedef struct _Kpval
{
	float vx;
	float Kp;
}Kpval ;



#endif // !_DATA_TYPE_H
