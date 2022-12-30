#include <REGX52.H>
#include "Delay.h"

//���Ŷ���
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_CS = P3^5;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;



/**
  *@brief	XPT2046 ADת��
  *@param	command
  *@return	ת���������
 */
unsigned int XPT2046_Read(unsigned char Cmd)
{
	unsigned int AdData = 0;
	unsigned char i = 0;
	
	//DCLK��ʼ������
	XPT2046_DCLK = 0;
	//DIN��ʼ������
	XPT2046_DIN = 0;
	//CS��ʼ������
	XPT2046_CS = 0;
	
	//�����ݷŵ�������
	for(i = 0; i < 8; i++)
	{
		
		XPT2046_DIN = Cmd & (0x80 >> i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	
	//�ȴ�ת��
	Delayms(1);
	
	//����
	for(i = 0; i < 16; i++)
	{
		
		if(XPT2046_DOUT) {AdData |= (0x8000 >> i);}
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	
	XPT2046_CS = 1;
	XPT2046_DOUT = 1;
	
	
	return AdData >> 4;
	
}