#include "LPC11xx.h"
#include "UART.h"

#define URAT_BPS 115200;
uint8_t num_in[10];		              //���ڽ������ݻ�����
volatile uint8_t getnew;	          //���ڽ��������ݵı�־
uint32_t num;  	                    //���ڽ������ݸ���