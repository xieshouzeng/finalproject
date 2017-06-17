#include "lpc11xx.h"

uint32_t table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};	


//延时
void delay(uint32_t i)
{
	while(i--);
}

//数码管初始化
void SHUMAGUAN_GPIOInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);      //使能IOCON时钟，可省略
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	LPC_SYSCON->SYSAHBCLKCTRL &=~ (1<<16);
	LPC_GPIO2->DIR |= 0xFFF;		               //打开引脚
}

//摄氏度显示
void SHUMAGUAN_Display(uint32_t value)              //摄氏度
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

//华氏度显示
void Fahrenheit_Display(uint32_t value)              //华氏度
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
