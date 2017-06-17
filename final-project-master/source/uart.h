#include "lpc11xx.h"

#ifndef _CK_H_
#define _CK_H_

extern void UART_Init(void);
extern void UART_SendByte(uint8_t ucDat);
extern void UART_SendStr(char *pucStr);


#endif
