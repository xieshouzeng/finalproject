#include "lpc11xx.h"

uint32_t table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};	


//��ʱ
void delay(uint32_t i)
{
	while(i--);
}

//����ܳ�ʼ��
void SHUMAGUAN_GPIOInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);      //ʹ��IOCONʱ�ӣ���ʡ��
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	LPC_SYSCON->SYSAHBCLKCTRL &=~ (1<<16);
	LPC_GPIO2->DIR |= 0xFFF;		               //������
}

//���϶���ʾ
void SHUMAGUAN_Display(uint32_t value)              //���϶�
{
	  LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value%1000%1000%10];
		LPC_GPIO2->DATA &=~(1<<11);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;

		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value%1000%100/10];
		LPC_GPIO2->DATA &=~(1<<10);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;

		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value%1000/100];
		LPC_GPIO2->DATA &=~(1<<9);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;
	
		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value/1000];
		LPC_GPIO2->DATA &=~(1<<8);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;
}

//���϶���ʾ
void Fahrenheit_Display(uint32_t value)              //���϶�
{
	  LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value%1000%1000%10];
		LPC_GPIO2->DATA &=~(1<<11);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;

		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value%1000%100/10];
		LPC_GPIO2->DATA &=~(1<<10);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;

		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value%1000/100];
		LPC_GPIO2->DATA &=~(1<<9);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;
	
		LPC_GPIO2->DATA &=~(0xff);
		LPC_GPIO2->DATA |= table[value/1000];
		LPC_GPIO2->DATA &=~(1<<8);
		delay(40);
		LPC_GPIO2->DATA = 0xFFF;
}
