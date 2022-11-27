#include <REGX52.H>
#include "Delay.h"

#define Matrix_Line_Out P0

//RCLK
sbit RCK = P3^5;
//SRCLK
sbit SRC = P3^6;
//SER
sbit SER = P3^4;



//*************************************************

//���ܣ�74HC595�����������������λ�䵽���λ
//�������ͣ�void
//�βΣ�unsigned char 

//*************************************************
void _74HC595_Write(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		//ȡSERΪbyte�ĸ�λ
		SER = byte & 0x80;
		//���ߴ���
		SRC = 1;
		//��λ
		SRC = 0;
		//byte����һλ��ȡ��һ��λ
		byte = byte << 1;
	}
	
	//�����ذ����ݴ��͹�ȥ
	RCK = 1;
	//��λ
	RCK = 0;
	
}

//*************************************************

//���ܣ�74HC595��ʼ��
//�������ͣ�void
//�βΣ�void

//*************************************************

void _74HC595_Initial()
{
	RCK = 0;
	SRC = 0;
}

//*************************************************

//���ܣ�LED������ʾ
//�������ͣ�void
//�βΣ��У����͵�_74HC595_Write������

//*************************************************
void MatrixScreen_Show(unsigned char row, byte)
{
	Matrix_Line_Out = ~(0x80 >> row-1);
	_74HC595_Write(byte);
	
}












