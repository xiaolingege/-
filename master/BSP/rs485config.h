#ifndef RS485CONFIG_H
#define RS485_CONFIG_H
/*-----------------------------*/
#include    "stm32f10x.h"
extern void AgvControlCOMConfig(void);
static void Rs485CtrlConfig(void);
extern void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data, uint16_t Len);;


/*-----------------------------*/
#endif
