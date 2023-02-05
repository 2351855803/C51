#include <REGX52.H>
#include <intrins.h>
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"
#include "DHT11.h"
#include "SYN6288.h"
//定义寄存器
#define Lcdout P0


//定义引脚
sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;



//**************************************************************
//----------------------------  Write_cmd 和 Write_data 差别在RS电平
//发送命令  RS = 0
void Write_cmd(unsigned char cmd)
{

	RS = 0;
	RW = 0;
	EN = 0;

	//单片机把要发送的数据放到数据总线里
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);

	
}
//**************************************************************
//发送数据 RS = 1
void Write_data(unsigned char cmd)
{

	RS = 1;
	RW = 0;
	EN = 0;

	//单片机把要发送的数据放到数据总线里
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);
	

}
//**************************************************************
void Lcd_initial()
{

	Write_cmd(0x01);
	Write_cmd(0x06);
	
	Write_cmd(0x0c);
	Write_cmd(0x38);
	

	
	Delayms(1);
	
	
}
//**************************************************************
void Lcd_write_string(char cmd, char* addr)
{
	while(*addr != '\0')
	{
		Write_cmd(cmd++);
		Write_data(*addr);
		addr++;
	}
}

//**************************************************************

//在第几行第几列显示数字
//形参列表（行，列，数字）

//**************************************************************
void Lcd_write_number(char line, char row ,unsigned char number)
{
	if(1 == line)
	{
		Write_cmd(0x80+row-1);
	
		Write_data((number/10)+0x30);
		Write_data((number%10)+0x30);
	}
	else if(2 == line)
	{
		Write_cmd(0xc0+row-1);
		
		Write_data((number/10)+0x30);
		Write_data((number%10)+0x30);
	}
}

/**
  *@brief	LCD显示开始界面
  *@param	void
  *@return	void
 */
void LCD_ShowBegin()
{
	char i;
	
	for(i = 15; i >= 0; i--)
	{
		Lcd_write_string(0x80+i,"Welcome to use!");
		Delayms(300);
	}
	for(i = 15; i >= 0; i--)
	{
		Lcd_write_string(0xc0+i,"Please set!   ->");
		Delayms(300);
	}
	SYN_FrameInfo(0, "[v5][t5]欢请使用请设置上下限");
	Delayms(10000);
	while(0xee != Matrix_key());
	Delayms(100);
	Write_cmd(0x01);
	Delayms(100);
	
	
}


/**
  *@brief	LCD显示设置温湿度界面
  *@param	void
  *@return	void
 */
void LCD_ShowSetTH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	Write_cmd(0x01);
	while(0xee != Matrix_key())
	{ 
		if(0xe7 == Matrix_key()) { Key_OnetouchSet(humHWarn,humLWarn,tmpHWarn,tmpLWarn);}
		Matrix_Set_DH(humHWarn,humLWarn,tmpHWarn,tmpLWarn);
		DHT11_SetAlarn(humHWarn,humLWarn,tmpHWarn,tmpLWarn);
		
		Lcd_write_string(0x80,"hum:");
		Lcd_write_string(0xc0,"tmp:");
		Lcd_write_string(0x85,"MAX");
		
		Lcd_write_number(1,9,*humHWarn);
		
		Lcd_write_string(0x8B,"MIN");		
		
		Lcd_write_number(1,15,*humLWarn);
		
		Lcd_write_string(0xC5,"MAX");
		
		Lcd_write_number(2,9,*tmpHWarn);
		
		Lcd_write_string(0xCB,"MIN");
		
		Lcd_write_number(2,15,*tmpLWarn);
	}
	Write_cmd(0x01);
	Delayms(1000);
}






