#include "lpc11xx.h"
#ifndef _ADC_H_
#define _ADC_H_

extern void Delay(uint32_t ulTime);
extern void ADC_Init(void);	           //ADC��ʼ��
extern uint32_t ADC_Read(void);	       //��ȡADC

#endif