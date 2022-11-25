#include <REGX52.H>
#include "UART.h"

int main()
{
	Uart_Init();
	while(1)
	{
		
	}
	
	
	return 0;
}

void UART_Routine() interrupt 4
{
	if(1 == RI)
	{
		P2 = SBUF;
		RI = 0;
		UART_Send(P2);
	}
}
