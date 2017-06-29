/******************** (C) COPYRIGHT 2013 www.armjishu.com  ***********************
 * 文件名  ：stm32f10x_it.c
 * 描述    ：实现STM32F103ZE神舟III号开发板STM32中断处理函数文件
 *           部分通用的一般不需要修改的中断处理函数放在"SZ_STM32F103ZE_LIB.c"文件中
 * 实验平台：STM32神舟开发板
 * 标准库  ：STM32F10x_StdPeriph_Driver V3.5.0
 * 作者    ：www.armjishu.com 
**********************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "SZ_STM32F103ZE_LIB.h"
#include    "rs485communicate.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**-------------------------------------------------------
  * @函数名 NMI_Handler
  * @功能   不可屏蔽中断的中断处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void NMI_Handler(void)
{
}

/**-------------------------------------------------------
  * @函数名 HardFault_Handler
  * @功能   硬件错误中断的中断处理函数
  *         可添加函数，现在为空while循环，便于仿真器捕捉
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**-------------------------------------------------------
  * @函数名 MemManage_Handler
  * @功能   存储器访问错误中断的中断处理函数
  *         可添加函数，现在为空while循环，便于仿真器捕捉
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**-------------------------------------------------------
  * @函数名 BusFault_Handler
  * @功能   总线访问错误中断的中断处理函数
  *         可添加函数，现在为空while循环，便于仿真器捕捉
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**-------------------------------------------------------
  * @函数名 UsageFault_Handler
  * @功能   用法错误中断的中断处理函数
  *         可添加函数，现在为空while循环，便于仿真器捕捉
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**-------------------------------------------------------
  * @函数名 SVC_Handler
  * @功能   系统服务中断的中断处理函数
  *         一般会被操作系统使用
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void SVC_Handler(void)
{
}

/**-------------------------------------------------------
  * @函数名 DebugMon_Handler
  * @功能   调试监控中断的中断处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void DebugMon_Handler(void)
{
}

/**-------------------------------------------------------
  * @函数名 PendSV_Handler
  * @功能   可挂起的系统服务请求处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void PendSV_Handler(void)
{
}

void USART2_IRQHandler(void)
{//  unsigned int i;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
// 	if(!(USART_GetITStatus(USART2,USART_IT_RXNE))); 
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);

	}
}

//void SysTick_Handler(void)
//{
// EnableSend();   
//}
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/******************* (C) COPYRIGHT 2013 www.armjishu.com *****END OF FILE****/
