#include "usart.h"

void usartConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOA, ENABLE);
#if _USART1_ENABLE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_Config(USART1, _USART1_BAUD);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = _USART1_TX_PIN;	            //USART1  TX
	GPIO_Init(_USART1_TX_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = _USART1_RX_PIN;	            // USART1 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 复用开漏输入
	GPIO_Init(_USART1_RX_PORT, &GPIO_InitStructure);
#endif

#if _USART2_ENABLE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_Config(USART2, _USART2_BAUD);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = _USART2_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_USART2_TX_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = _USART2_RX_PIN;
	GPIO_Init(_USART2_RX_PORT, &GPIO_InitStructure);
#endif
}
static void USART_Config(USART_TypeDef* USARTx, u32 rate)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = rate;					//速率115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式
	USART_Init(USARTx, &USART_InitStructure);							//配置串口参数函数
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);                      //使能接收中断
	USART_Cmd(USARTx, ENABLE);
}
