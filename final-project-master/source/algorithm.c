#include "lpc11xx.h"
#include "stdio.h"
#include "math.h"

#define MAX 16

//��ѹת�����¶�

uint32_t Rd2_temp(int ulADCData)
{
	float R;               
  float Re[MAX]={0.3952,0.5046,0.6510,0.8502,1.124,1.506,2.047,2.823,3.958,5.648,8.221,12.124,18.68,29.37,47.73,80.36};
	int Tem[MAX]={130,120,110,100,90,80,70,60,50,40,30,20,10,0,-10,-20};
	float rule;
	float Temp;
	uint8_t n;
	
	R = (ulADCData*10*1.0)/(3.3-(ulADCData/1000));            // ���裬���������ѹ����
	R = R/1000;																				     //ת����λΪ Kŷķ
	if((R<0.3956)||(R>80.36))                              //�ж��Ƿ���������跶Χ֮��
		Temp = 0;
	else
	{
		for(n=0;n<16;n++)
		{
			if((R>Re[n])&&(R<Re[n+1]))
			{
				rule = (Re[n+1]-Re[n])/10;                            //����ÿ���̶�����Ӧ����ֵ
				Temp = Tem[n+1] - (R-Re[n])/rule;
			}
		}
	}

	return Temp*100/10;                                          //����һλС��
}

