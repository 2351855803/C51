#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "AT24C02.h"

/**
  *@brief	ͨ��������ѡ��ģʽ
  *@param	
  *@return	���������ģʽ  
 */
unsigned char Matrix_key()
{
	unsigned char n,m;
	P1=0xf0;
	
	//��⵽�а������£�����λ����һ�����0
	if((P1&0xf0)!=0xf0);
	{
		Delayms(10);
			
		if((P1&0xf0)!=0xf0);
		{
			//ȡ����λ
			n=P1&0xf0;
			
			P1=0x0f;

			//ȡ����λ
			m=P1&0x0f;
			
			return(n+m);
		}
	}
}

/**
  *@brief	ͨ����������������¶�ʪ��������
  *@param	�ֱ��� ʪ������ ʪ������ �¶����� �¶�����
  *@return  void
 */
void Matrix_Set_DH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	//ʪ�������޼Ӽ�
	if(0x77 == Matrix_key()) {(*humHWarn)++; AT24C02_Write(1,(*humHWarn)); while(0x77 == Matrix_key());}
	if(0x7b == Matrix_key()) {(*humHWarn)--; AT24C02_Write(1,(*humHWarn)); while(0x7b == Matrix_key());}
	if(0x7d == Matrix_key()) {(*humLWarn)++; AT24C02_Write(2,(*humLWarn)); while(0x7d == Matrix_key());}
	if(0x7e == Matrix_key()) {(*humLWarn)--; AT24C02_Write(2,(*humLWarn)); while(0x7e == Matrix_key());}
	
	//�¶������޼Ӽ�
	if(0xb7 == Matrix_key()) {(*tmpHWarn)++; AT24C02_Write(3,(*tmpHWarn)); while(0xb7 == Matrix_key());}
	if(0xbb == Matrix_key()) {(*tmpHWarn)--; AT24C02_Write(3,(*tmpHWarn)); while(0xbb == Matrix_key());}
	if(0xbd == Matrix_key()) {(*tmpLWarn)++; AT24C02_Write(4,(*tmpLWarn)); while(0xbd == Matrix_key());}
	if(0xbe == Matrix_key()) {(*tmpLWarn)--; AT24C02_Write(4,(*tmpLWarn)); while(0xbe == Matrix_key());}
	

}










