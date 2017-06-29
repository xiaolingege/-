#ifndef HARDWARE_H
#define HARDWARE_H
#include "stm32f10x.h"

extern void HardWareInit(void);
extern void NVIC_Configuration(void);
static void USART_Config(USART_TypeDef* USARTx, u32 rate);

#endif



