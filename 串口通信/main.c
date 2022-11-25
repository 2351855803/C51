#include <REGX52.H>
#include "Delay.h"
#include "UART.h"



int main()
{
	//定义i
	unsigned char i = 0; 
	
	//串口初始化
	Uart_Init();
	
	//当按下K1按键，开始逐个发送数据
	while(P3_1 == 1);
	
	while(1)
	{
		//*************************************************
		
		//每隔一秒发一个递增的数
		
		//*************************************************
		Uart_Send(i++);
		Delayms(1000);
		
		
		
		
	}
	
	
	return 0;
}

