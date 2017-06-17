#include "LPC11XX.H"
#include "stdio.h"
#include "string.h"
#include "ADC.h"


//��ʱ
void Delay(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}

//ADC��ʼ��
void ADC_Init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);              //ʹ��IOCONʱ��
	LPC_IOCON->PIO1_11 &=~ 0xBF;                  //����11Ϊģ������ģʽ
	LPC_IOCON->PIO1_11 |= 0x01;
	LPC_SYSCON->PDRUNCFG &=~ (0x01<<4);            //�ϵ�
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);            //ʹ��ADC
	LPC_ADC->CR=(0x01<<7)|														//ѡ��ͨ��AD1
							((SystemCoreClock/1000000-1)<<8)|			//ʱ������
							(0<<16)|															//�������ģʽ
							(0<<17)|															//ÿ��ת��ռ�õ�ʱ������������000 - 11��
							(0<<24)|															//�Ȳ�����
							(0<<27);															//����������ת��
}


//��ȡADC
uint32_t ADC_Read(void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	ulADCData = 0;
	
		for(i=0;i<10;i++)
	  {
			LPC_ADC->CR |= (1<<24);        //����ת��
			while((LPC_ADC->DR[7]&0x80000000)==0);			//��ȡ���
			LPC_ADC->CR |= (1<<24);        //�����ظ�
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf = LPC_ADC->DR[7];     //��ȡ���ݼĴ���
			ulADCBuf = (ulADCBuf>>6)&0x3ff;								
			ulADCData += ulADCBuf;           //�Լ�
		}
		ulADCData = ulADCData/10;             //ȡƽ�������˲�
		ulADCData = (ulADCData*3300)/1024;   //����ת����ģ��
		return ulADCData;
}
