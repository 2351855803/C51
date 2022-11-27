#include <REGX52.H>
#include "UART.h"
#include "Delay.h"
#include "LCD1602.h"
#include "Timer1.h"

//计数
int count = 0;
//随一秒加一
int i = 0;
//临时存储变量
char temp;


int main()
{
	//串口初始化
	UART_Init();
	//LCD初始化
	Lcd_initial();
	//定时器0初始化
	//Timer1_Init();
	
	
	while(1)
	{
		Write_cmd(0x80+i);
		Write_data(temp);
	}
	
	return 0;
}

//定时器0中断
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

//串口中断
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