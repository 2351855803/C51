#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "AT24C02.h"
#include "SYN6288.h"
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


/**
  *@brief	ͨ��ѡ��������һ������
  *@param	��ʪ��������Ԥ��ֵ
  *@return  void
 */
void Key_OnetouchSet(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	char i;
	Write_cmd(0x01);
	Delayms(100);
	for(i = 15; i >= 0; i--)
	{
		Lcd_write_string(0x80+i,"OnetouchSet: ");
		Delayms(300);
	}	
	SYN_FrameInfo(0, "[v5][t5]һ������ģʽ");
	Delayms(5000);

	while(0xee != Matrix_key())
	{
		//һ�����÷��������ʪ��
		if(0xd7 == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Toamato!");
			(*humHWarn) = 60;
			AT24C02_Write(1,(*humHWarn));
			Delayms(20);
			(*humLWarn) = 30;
			AT24C02_Write(2,(*humLWarn));
			Delayms(20);
			(*tmpHWarn) = 30;
			AT24C02_Write(3,(*tmpHWarn));
			Delayms(20);
			(*tmpLWarn) = 25;
			AT24C02_Write(4,(*tmpLWarn));
			SYN_FrameInfo(0, "[v5][t5]���÷��ѳɹ�");
			Delayms(5000);
		}
		//һ���������������ʪ��
		if(0xdb == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Eggplant!");
			(*humHWarn) = 40;
			AT24C02_Write(1,(*humHWarn));
			Delayms(20);
			(*humLWarn) = 30;
			AT24C02_Write(2,(*humLWarn));
			Delayms(20);
			(*tmpHWarn) = 30;
			AT24C02_Write(3,(*tmpHWarn));
			Delayms(20);
			(*tmpLWarn) = 15;
			AT24C02_Write(4,(*tmpLWarn));
			SYN_FrameInfo(0, "[v5][t5]�������ӳɹ�");
			Delayms(5000);
		}		
		//һ�����ú��ܲ������ʪ��
		if(0xdd == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Carrot!");
			(*humHWarn) = 50;
			AT24C02_Write(1,(*humHWarn));
			Delayms(20);
			(*humLWarn) = 35;
			AT24C02_Write(2,(*humLWarn));
			Delayms(20);
			(*tmpHWarn) = 30;
			AT24C02_Write(3,(*tmpHWarn));
			Delayms(20);
			(*tmpLWarn) = 13;
			AT24C02_Write(4,(*tmpLWarn));
			SYN_FrameInfo(0, "[v5][t5]���ú��ܲ��ɹ�");
			Delayms(5000);
		}		
		//һ�����þ²������ʪ��
		if(0xde == Matrix_key())
		{
			Lcd_write_string(0xc0,"            ");
			Lcd_write_string(0xc0,"Leek!");
			(*humHWarn) = 70;
			AT24C02_Write(1,(*humHWarn));
			Delayms(20);
			(*humLWarn) = 40;
			AT24C02_Write(2,(*humLWarn));
			Delayms(20);
			(*tmpHWarn) = 25;
			AT24C02_Write(3,(*tmpHWarn));
			Delayms(20);
			(*tmpLWarn) = 20;
			AT24C02_Write(4,(*tmpLWarn));
			SYN_FrameInfo(0, "[v5][t5]�����۲˳ɹ�");
			Delayms(5000);
		}
	}
	Write_cmd(0x01);
	Delayms(100);
}




