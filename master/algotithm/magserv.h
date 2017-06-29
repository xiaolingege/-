#ifndef MAGSERV_H
#define MAGSERV_H
#include    "stm32f10x.h"
#include    "stdbool.h"

#define MAGRCVSIZE  (15)

static float StationCalc(const u8 * MagSense);
static  bool isCheckHead(const u8 * head);
extern void MagToSpeed(void);
static float MagCenterCalc(u32 magsenseBuffer);
static float PIDCalc(float err);

#endif
