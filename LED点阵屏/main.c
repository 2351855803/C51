#include <REGX52.H>
#include "MatrixScreen.h"
#include "Delay.h"
#include "UART.h"


unsigned char temp;

int main()
{

	unsigned char i = 1;
	
	//74HC595��ʼ��
	_74HC595_Initial();
	//UART��ʼ��
	UART_Initial();
	
	
	while(1)
	{
		
		MatrixScreen_Show(i++,temp);
		UART_Send(temp);
		Delayms(1000);
		if(8 == i)
		{
			i = 1;
		}
		
	}
	
	
	return 0;
}

//���ڶ�ʱ���ж�
void UART_Routine() interrupt 4
{
	if(RI)
	{
		temp = SBUF;
		RI = 0;
	}
}