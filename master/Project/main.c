#include "rs485config.h"
#include "hardware.h"
#include "rs485communicate.h"
#include "magserv.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define SPEEDSENDTASKPRIO   2
#define MAGSENSEQUERYPRIO   3
#define SPEEDREADTASKPRIO	1

#define SPEEDSENDTASKSTK    500
#define MAGSENSEQUERYSTK    200
#define SPEEDREADTASKSTK	100		

void SpeedSendTask(void *pvParameters);
void MagSenseQueryTask(void *pvParameter);
void SpeedReadTask(void *pvParameters);

u8 txbuffer[5] = { 1, 2, 3, 4, 5 };
TaskHandle_t    SpeedSendTaskHandle;//速度发送任务句柄
TaskHandle_t    MagSenseQueryHandle;//磁传感器查询句柄
TaskHandle_t	SpeedReadTaskHandle;

/*---------------------------------------------------------------------------------------------*/
int main(void)
{
	HardWareInit();
	AgvControlCOMConfig();
	NVIC_Configuration();
	/*创建速度发送任务*/
	xTaskCreate((TaskFunction_t)SpeedSendTask,
		(const char*)"SpeedSendTask",
		(u16)SPEEDSENDTASKSTK,
		(void*)NULL,
		(UBaseType_t)SPEEDSENDTASKPRIO,
		(TaskHandle_t *)&SpeedSendTaskHandle);
	/*创建磁传感器查询任务*/
	xTaskCreate((TaskFunction_t)MagSenseQueryTask,
		(const char*)"MagSenseQuery",
		(u16)MAGSENSEQUERYSTK,
		(void*)NULL,
		(UBaseType_t)MAGSENSEQUERYPRIO,
		(TaskHandle_t *)&MagSenseQueryHandle);
	/*创建速度读取任务*/
	xTaskCreate((TaskFunction_t)SpeedReadTask,
		(const char*)"SpeedReadTask",
		(u16)SPEEDREADTASKSTK,
		(void *)NULL,
		(UBaseType_t)SPEEDREADTASKPRIO,
		(TaskHandle_t *)&SpeedReadTaskHandle);
	vTaskStartScheduler();
}

/*---------------------------------------------------------------------------------------------*/
//速度控制任务
void SpeedSendTask(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while (1)
	{

		MagToSpeed();
		vTaskDelay(6);
	}
}
//磁传感器查询任务

/*---------------------------------------------------------------------------------------------*/
void MagSenseQueryTask(void *pvParameters)
{
	static u8 TxBufferToQueryMagsense[7] = { 0x52, 0x4D, 0x67, 0x73, 0x77 , 0x5e, 0x69 };
	pvParameters = (void *)pvParameters;

	while (1)
	{

		USART_OUT(USART1, TxBufferToQueryMagsense, 7);
		vTaskDelay(50);
	}
}

void SpeedReadTask(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while (1)
	{
	
	}
}


/******************* (C) COPYRIGHT 2013 www.armjishu.com *****END OF FILE****/
