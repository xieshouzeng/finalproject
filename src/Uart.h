#ifndef __Uart_H__
#define __Uart_H__

#include "LPC11xx.h"

extern uint8_t UART_GetByte(void);
extern void UART_SendByte(uint8_t ucDat);
extern void UART_SendStr(char *pucStr);
extern void UART_IRQHandler (void);

#endif
