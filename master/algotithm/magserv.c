#include "magserv.h"

#define MAGSERVPI 0.05f

const Kpval Kparr[] = { { 0,0 },{ 0.4, 0.005 } };
static float CarSpeedVx = 0;
static float CarSpeedVw = 0;

u8 MagReceiveDate[MAGRCVSIZE] = { 0 };
u8 MagReceiveCount = 0;

/*---------------------------------------------------------------------------------------------*/
static float positionDeviation(const u8 * MagSense)
{

	static float StationForReturn = 0;
	u32 magDate = 0;
	if (MagReceiveCount >= 10)
	{
		if (isCheckHead(MagSense))
		{
			magDate = (MagSense[5] << 16) | (MagSense[6] << 8) | (MagSense[7]);
			MagReceiveCount = 0;
			if (0 != magDate)
			{
				StationForReturn = MagCenterCalc(magDate);
			}
			else
			{
				CarSpeedVx = 0;
				StationForReturn = 0;
			}
		}
		MagReceiveCount = 0;
	}
	return StationForReturn;
}

/*---------------------------------------------------------------------------------------------*/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)

	{
		MagReceiveDate[MagReceiveCount++] = USART_ReceiveData(USART1);
		if (MagReceiveDate[0] != 0x52)
		{
			MagReceiveCount = 0;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);

	}
}

/*---------------------------------------------------------------------------------------------*/
static  bool isCheckHead(const u8 * head)
{
	u8 hedbuffer[5] = { 0x52, 0x4D, 0x67, 0x73, 0x77 };
	u8 i = 0;
	for (i = 0; i < 5; i++)
	{
		if (head[i] != hedbuffer[i])
		{
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------------------------------*/
void MagToSpeed(void)
{
	float positionVal;
	positionVal = positionDeviation(MagReceiveDate);
	CarSpeedVx = localPlanVx(0, FALSE, CarSpeedVx, FALSE);
	CarSpeedVw = localPlanVw(0, CarSpeedVx, FALSE);
	//计算偏差值
	//根据偏差值、站点信息、当前速度与障碍物信息计算vx
	//根据偏差值、线速度值与限位开关信息得到模糊规则的KP、KI、KD并计算vw
	//发送速度到驱动器
//	CarSpeedVw = PIDCalc(positionVal);
	SendSpeedToCtrl(CarSpeedVx, 0);
}


/*---------------------------------------------------------------------------------------------*/
static float MagCenterCalc(u32 magsenseBuffer)
{
	float weight[16];
	float magCenterForReturn = 0;
	float signal[16];
	u8 count = 0;
	u8 i = 0;
	signal[15] = 1 & magsenseBuffer;
	for (i = 0; i < 16; i++)
	{
		weight[i] = (float)i - 7.5f;
	}
	for (i = 8; i < 16; i++)
	{
		signal[i - 1] = 1 & (magsenseBuffer >> (i));
	}
	for (i = 1; i < 8; i++)
	{
		signal[i - 1] = 1 & (magsenseBuffer >> (16 + i));
	}
	for (i = 0; i < 16; i++)
	{
		if (signal[i])
		{
			count++;
		}
		magCenterForReturn += (weight[i] * signal[i]);
	}
	return (magCenterForReturn / (float)count* 10.0f);

}

/*---------------------------------------------------------------------------------------------*/
static float PIDCalc(float err)
{
	float Control = 0;
	Control = MAGSERVPI * err;
	return  Control;
}

static float localPlanVx(float err, BOOL station, float currentVx, BOOL hinder)
{
	float vx = 0;
	if (TRUE == hinder)
	{
		vx = 0.0f;
	}
	else if (TRUE == station)
	{
		vx = 0.25f;
		return vx;
	}
	else
	{
		vx = _MAX_CAR_SPEED;
	}
	if (vx > currentVx)
	{
		vx = currentVx + _CAR_SPEED_STEP;
	}
	else if (vx < currentVx)
	{
		vx = currentVx - _CAR_SPEED_STEP;
	}
	return vx;
}

static float localPlanVw(float err, float targetVx, BOOL limitSwitch)
{
	float PI = 0.05f;
	float vw = 0;
	if (TRUE == limitSwitch)
	{
		vw = 0;
		return vw;
	}
	else
	{

		vw = err * PI;
	}
	return vw;
}



