#include <REGX52.H>
#include "Delay.h"
#include "UART.h"



int main()
{
	//����i
	unsigned char i = 0; 
	
	//���ڳ�ʼ��
	Uart_Init();
	
	//������K1��������ʼ�����������
	while(P3_1 == 1);
	
	while(1)
	{
		//*************************************************
		
		//ÿ��һ�뷢һ����������
		
		//*************************************************
		Uart_Send(i++);
		Delayms(1000);
		
		
		
		
	}
	
	
	return 0;
}

