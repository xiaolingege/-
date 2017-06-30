#include "speedread.h"
#include "stm32f10x.h"
#include "rs485config.h"
#include "datatype.h"

static u8 SpeedReadBuff[20] = { 0 };
void speedQuery(void)
{

	
}

void speedRcv(void)
{

}

BOOL isRcvMsg(u8 * ptr)
{

	return TRUE;
}


void USART2_IRQHandler(void)
{//  unsigned int i;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
		// 	if(!(USART_GetITStatus(USART2,USART_IT_RXNE))); 
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);

	}
}



