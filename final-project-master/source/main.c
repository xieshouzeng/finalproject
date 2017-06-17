#include "lpc11xx.h"
#include "ADC.h"
#include "display.h"
#include "uart.h"
#include "algorithm.h"
#include "key.h"
#include <stdio.h>

static uint32_t Temp;          // ��̬����
int biaozhi=0;                  //���ñ�־λ
extern char GcRcvBuf[20];         //����������

//��ʱ
void Delay_ms(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}


//�����жϷ�����  
void PIOINT3_IRQHandler()
{
	int i;
	if((LPC_GPIO3->MIS&(1<<1)) == (1<<1))  //�ж��жϰ���λ�� 
	{
		Delay_ms(200);
		biaozhi++;
		if(biaozhi>2) biaozhi=0;
		LPC_GPIO3->IC = 0xFFF;            //�ж����
	}
}


//������
int main()
{																			  	
	uint32_t t;
	uint32_t temp;
	
	SHUMAGUAN_GPIOInit();     //����ܳ�ʼ��
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
