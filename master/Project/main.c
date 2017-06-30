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
TaskHandle_t    SpeedSendTaskHandle;//�ٶȷ���������
TaskHandle_t    MagSenseQueryHandle;//�Ŵ�������ѯ���
TaskHandle_t	SpeedReadTaskHandle;

/*---------------------------------------------------------------------------------------------*/
int main(void)
{
	HardWareInit();
	AgvControlCOMConfig();
	NVIC_Configuration();
	/*�����ٶȷ�������*/
	xTaskCreate((TaskFunction_t)SpeedSendTask,
		(const char*)"SpeedSendTask",
		(u16)SPEEDSENDTASKSTK,
		(void*)NULL,
		(UBaseType_t)SPEEDSENDTASKPRIO,
		(TaskHandle_t *)&SpeedSendTaskHandle);
	/*�����Ŵ�������ѯ����*/
	xTaskCreate((TaskFunction_t)MagSenseQueryTask,
		(const char*)"MagSenseQuery",
		(u16)MAGSENSEQUERYSTK,
		(void*)NULL,
		(UBaseType_t)MAGSENSEQUERYPRIO,
		(TaskHandle_t *)&MagSenseQueryHandle);
	/*�����ٶȶ�ȡ����*/
	xTaskCreate((TaskFunction_t)SpeedReadTask,
		(const char*)"SpeedReadTask",
		(u16)SPEEDREADTASKSTK,
		(void *)NULL,
		(UBaseType_t)SPEEDREADTASKPRIO,
		(TaskHandle_t *)&SpeedReadTaskHandle);
	vTaskStartScheduler();
}

/*---------------------------------------------------------------------------------------------*/
//�ٶȿ�������
void SpeedSendTask(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while (1)
	{

		MagToSpeed();
		vTaskDelay(6);
	}
}
//�Ŵ�������ѯ����

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
