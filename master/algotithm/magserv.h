#ifndef MAGSERV_H
#define MAGSERV_H
#include "stm32f10x.h"
#include "datatype.h"
#include "stm32f10x.h"
#include "rs485communicate.h"

#define  _MAX_CAR_SPEED (0.45f)
#define _CAR_SPEED_STEP (0.002f)
#define MAGRCVSIZE  (15)

static float positionDeviation(const u8 * MagSense);
static  bool isCheckHead(const u8 * head);
extern void MagToSpeed(void);
static float MagCenterCalc(u32 magsenseBuffer);
static float PIDCalc(float err);
static  float localPlanVx(float err, BOOL station, float currentVx, BOOL hinder);
static float localPlanVw(float err, float targetVx, BOOL limitSwitch);

#endif
