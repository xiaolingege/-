#ifndef _SPEED_READ_H
#define _SPEED_READ_H
#include "stm32f10x.h"
#include "datatype.h"


void speedQuery(void);
void speedRcv(void);
static BOOL isRcvMsg(u8 * ptr);
#endif // !_SPEED_READ_H
