#include "lpc11xx.h"
#include "ADC.h"
#include "display.h"
#include "uart.h"
#include "algorithm.h"
#include "key.h"
#include <stdio.h>

static uint32_t Temp;          // 静态变量
int biaozhi=0;                  //设置标志位
extern char GcRcvBuf[20];         //缓冲区数组

//延时
void Delay_ms(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}


//按键中断服务函数  
void PIOINT3_IRQHandler()
{
	int i;
	if((LPC_GPIO3->MIS&(1<<1)) == (1<<1))  //判断中断按键位数 
	{
		Delay_ms(200);
		biaozhi++;
		if(biaozhi>2) biaozhi=0;
		LPC_GPIO3->IC = 0xFFF;            //中断清除
	}
}


//主函数
int main()
{																			  	
	uint32_t t;
	uint32_t temp;
	
	SHUMAGUAN_GPIOInit();     //数码管初始化
	ADC_Init();
	UART_Init();
	GPIOInit();									  		
	interupt();
while(1)
	{ 
		Temp = Rd2_temp(ADC_Read());  	
		if(biaozhi==0)
				SHUMAGUAN_Display(Temp/10);      
		if(biaozhi==1){
			temp = 32+Temp/10 * 1.8;			
				Fahrenheit_Display(temp);
		}
		if(biaozhi==2){
		sprintf(GcRcvBuf,"Temp=%4d C\r\n",Temp);
		UART_SendStr(GcRcvBuf);
		Delay_ms(200);
	}
	}
}
