#include    "rs485config.h"
#include    "stm32f10x.h"

#define     RS485CTRLPort    GPIOF
#define     RS485CTRLPin     GPIO_Pin_11


/*---------------------------------------------------------------------------------------------*/
void AgvControlCOMConfig(void)
{
    Rs485CtrlConfig();
 //   Rs485Config();
}

/*---------------------------------------------------------------------------------------------*/
static void Rs485CtrlConfig(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = RS485CTRLPin; 		 //与PF11管脚连接
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RS485CTRLPort, &GPIO_InitStructure);
}

/*---------------------------------------------------------------------------------------------*/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data, uint16_t Len)
{
    uint16_t i;
    for (i = 0; i < Len; i++)
    {
        USART_SendData(USARTx, Data[i]);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);      //判断是否发送完成。
    }
}












