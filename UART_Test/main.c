#include <REGX52.H>
#include "UART.h"
#include "Delay.h"
#include "LCD1602.h"
#include "Timer1.h"

//����
int count = 0;
//��һ���һ
int i = 0;
//��ʱ�洢����
char temp;


int main()
{
	//���ڳ�ʼ��
	UART_Init();
	//LCD��ʼ��
	Lcd_initial();
	//��ʱ��0��ʼ��
	//Timer1_Init();
	
	
	while(1)
	{
		Write_cmd(0x80+i);
		Write_data(temp);
	}
	
	return 0;
}

//��ʱ��0�ж�
void Timer1_Routine() interrupt 1
{
	TH0 = (65535-10000);
	TL0 = (65535-10000);
	count++;
	if(100 == count)
	{
		i++;
		UART_Send(i);
		count = 0;
	}
}

//�����ж�
void UART_Routine() interrupt 4
{
	if(RI)
	{
		i++;
		temp = SBUF;
		UART_Send(temp);
		RI = 0;
		
	}
}