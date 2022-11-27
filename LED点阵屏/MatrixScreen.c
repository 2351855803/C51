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

//功能：74HC595输出，输入的数据最高位变到最低位
//返回类型：void
//形参：unsigned char 

//*************************************************
void _74HC595_Write(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		//取SER为byte的高位
		SER = byte & 0x80;
		//拉高触发
		SRC = 1;
		//复位
		SRC = 0;
		//byte左移一位，取下一个位
		byte = byte << 1;
	}
	
	//上升沿把数据传送过去
	RCK = 1;
	//复位
	RCK = 0;
	
}

//*************************************************

//功能：74HC595初始化
//返回类型：void
//形参：void

//*************************************************

void _74HC595_Initial()
{
	RCK = 0;
	SRC = 0;
}

//*************************************************

//功能：LED点阵显示
//返回类型：void
//形参：列，发送到_74HC595_Write的数据

//*************************************************
void MatrixScreen_Show(unsigned char row, byte)
{
	Matrix_Line_Out = ~(0x80 >> row-1);
	_74HC595_Write(byte);
	
}












