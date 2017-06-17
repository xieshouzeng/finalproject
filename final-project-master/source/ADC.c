#include "LPC11XX.H"
#include "stdio.h"
#include "string.h"
#include "ADC.h"


//延时
void Delay(uint32_t ulTime){
	uint32_t i;
	i=0;
	while(ulTime--){
		for(i=0;i<5000;i++);
	}
}

//ADC初始化
void ADC_Init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);              //使能IOCON时钟
	LPC_IOCON->PIO1_11 &=~ 0xBF;                  //配置11为模拟输入模式
	LPC_IOCON->PIO1_11 |= 0x01;
	LPC_SYSCON->PDRUNCFG &=~ (0x01<<4);            //上电
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);            //使能ADC
	LPC_ADC->CR=(0x01<<7)|														//选用通道AD1
							((SystemCoreClock/1000000-1)<<8)|			//时钟设置
							(0<<16)|															//软件控制模式
							(0<<17)|															//每次转换占用的时钟数，这里是000 - 11个
							(0<<24)|															//先不启动
							(0<<27);															//上升沿启动转换
}


//读取ADC
uint32_t ADC_Read(void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	ulADCData = 0;
	
		for(i=0;i<10;i++)
	  {
			LPC_ADC->CR |= (1<<24);        //立即转换
			while((LPC_ADC->DR[7]&0x80000000)==0);			//读取完成
			LPC_ADC->CR |= (1<<24);        //丢掉重复
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf = LPC_ADC->DR[7];     //读取数据寄存器
			ulADCBuf = (ulADCBuf>>6)&0x3ff;								
			ulADCData += ulADCBuf;           //自加
		}
		ulADCData = ulADCData/10;             //取平均数，滤波
		ulADCData = (ulADCData*3300)/1024;   //数字转换成模拟
		return ulADCData;
}
