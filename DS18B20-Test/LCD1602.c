#include <REGX52.H>
#include <intrins.h>
#include "Delay.h"

//����Ĵ���
#define Lcdout P0


//��������
sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;



//**************************************************************
//----------------------------  Write_cmd �� Write_data �����RS��ƽ
//��������  RS = 0
void Write_cmd(unsigned char cmd)
{

	RS = 0;
	RW = 0;
	EN = 0;

	//��Ƭ����Ҫ���͵����ݷŵ�����������
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);

	
}
//**************************************************************
//�������� RS = 1
void Write_data(unsigned char cmd)
{

	RS = 1;
	RW = 0;
	EN = 0;

	//��Ƭ����Ҫ���͵����ݷŵ�����������
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

//�ڵڼ��еڼ�����ʾ����
//�β��б��У��У����֣�

//**************************************************************
void Lcd_write_number(char line, char row ,unsigned char number)
{
	if(1 == line)
	{
		Write_cmd(0x80+row-1);
		Write_data((number/100)+0x30);
		Write_data((number/10%10)+0x30);
		Write_data((number%10)+0x30);
	}
	else if(2 == line)
	{
		Write_cmd(0xc0+row-1);
		Write_data((number/100)+0x30);
		Write_data((number/10%10)+0x30);
		Write_data((number%10)+0x30);
	}
}

