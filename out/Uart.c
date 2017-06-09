#include "LPC11xx.h"
#include "UART.h"

#define URAT_BPS 115200;
uint8_t num_in[10];		              //串口接收数据缓冲区
volatile uint8_t getnew;	          //串口接收新数据的标志
uint32_t num;  	                    //串口接收数据个数