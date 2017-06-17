#include "lpc11xx.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"

#define UART_BPS 9600
volatile uint8_t GucRcvNew;
uint8_t GucRcvBuf[10];
uint32_t GulNum;
char GcRcvBuf[20];

//串口初始化
void UART_Init(void){
	uint16_t usFdiv;
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_6 |= 0x01;                 //RXD
	LPC_IOCON->PIO1_7 |= 0x01;                 //TXD
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV = 0x01;                 //时钟分频
	
	LPC_UART->LCR = 0x83;                 //允许设置波特率
	usFdiv = (SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;            //设置波特率
	LPC_UART->DLM = usFdiv/256;
	LPC_UART->DLL = usFdiv%256;
	LPC_UART->LCR = 0x03;       //锁定波特率
	LPC_UART->FCR = 0x07;
	
	NVIC_EnableIRQ(UART_IRQn);
	LPC_UART->IER = 0x01;
}

//查询法查询数据
void UART_SendByte(uint8_t ucDat){
	LPC_UART->THR = ucDat;   //写入数据
	while((LPC_UART->LSR&0x40)==0);     //等待数据发送完毕
}

//发送字符串
void UART_SendStr(char *pucStr){
	while(1){
		if(*pucStr=='\0')     //遇到结束符，退出
			break;
		else
			UART_SendByte(*pucStr++);
	}
}

//串口中断
void UART_IRQHandler(void)
{

	uint32_t IRQ_ID;
	
	IRQ_ID = LPC_UART->IIR;
	IRQ_ID = ((IRQ_ID>>1)&0x7);
	if(IRQ_ID == 0x02){					
		sprintf(GcRcvBuf,"V:=%4d mV\r\n", ADC_Read());
		UART_SendStr(GcRcvBuf);
	}
	LPC_UART->FCR = 0x07;		
}
