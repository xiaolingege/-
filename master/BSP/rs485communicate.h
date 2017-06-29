#ifndef RS485COMMUNICATE_H
#define RS485COMMUNICATE_H
#include    "stm32f10x.h"
#include    "stdbool.h"



//static bool isSendTime(void);
extern void SendSpeedToCtrl(float vx, float w);
static u16 CRC16(u8 *puchMsg, u16 usDataLen );

#endif

