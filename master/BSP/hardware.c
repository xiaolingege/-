#include "hardware.h"
#include "usart.h"
/*---------------------------------------------------------------------------------------------*/
void HardWareInit(void)
{
	usartConfig();
}

/*---------------------------------------------------------------------------------------------*/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			     	//设置串口中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			     	//设置串口中断
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*---------------------------------------------------------------------------------------------*/







