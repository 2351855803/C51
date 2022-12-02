#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "UART.h"



unsigned char second = 30;
unsigned char minute = 30;
unsigned char hours = 10;
unsigned char timeOption = 1;


//��������ģʽ
sbit intoTimeSet = P3^1;
//��������߷ֻ���Сʱ
sbit sellect = P3^0;
sbit timeAdd = P3^2;
sbit timesub = P3^3;

//��������Set���ж�����
bit timeSetkey = 0;


//��鰴���Ƿ��½���ʱ������ģʽ
void checky_timeSet()
{
	if(!intoTimeSet)
	{
		Delayms(10);
		if(!intoTimeSet)
		{
			Delayms(1000);
			timeSetkey = ~timeSetkey;
		}
	}
}

void checky_sellect()
{
	if(!sellect)
	{
		Delayms(10);
		if(!sellect)
		{
			Delayms(10);
			timeOption += 1;
			if(4 == timeOption)
			{
				timeOption = 1;
			}
			
		}
	}
}

void checky_add()
{
	if(!timeAdd)
	{
		Delayms(10);
		if(!timeAdd)
		{
			Delayms(10);
			if(1 == timeOption)
			{
				hours++;
			}
			else if(2 == timeOption)
			{
				minute++;
			}
			else if(3 == timeOption)
			{
				second++;
			}
		
			
		}
	}
}

void checky_sub()
{
	if(!timesub)
	{
		Delayms(10);
		if(!timesub)
		{
			Delayms(10);
			if(1 == timeOption)
			{
				hours--;
			}
			else if(2 == timeOption)
			{
				minute--;
			}
			else if(3 == timeOption)
			{
				second--;
			}
		
			
		}
	}
}
int main()
{
	//LCD1602��ʼ��
	Lcd_initial();
	//DS1302��ʼ��
	DS1302_Init();
	//���ڳ�ʼ��
	UART_Init();
	
	//���д����
	DS1302_WriteByte(0x8e,0x00);
	
	Lcd_write_string(0x80,"NowTime:");
	
	Lcd_write_string(0xc2,":");
	Lcd_write_string(0xc5,":");
	
	//ʮ������
	//д��������ݣ�16���ƣ�
	//�� ���� Сʱ������
	//��
	DS1302_WriteByte(0x80,second/10*16 + second%10);
	//����
	DS1302_WriteByte(0x82,minute/10*16 + minute%10);
	//Сʱ
	DS1302_WriteByte(0x84,hours/10*16 + hours%10);
	
	while(1)
	{
		
		checky_timeSet();
		while(timeSetkey)
		{
			//���Ͻ���ʾSet
			Lcd_write_string(0x8d,"Set");
			Lcd_write_number(2,1,hours);
			Lcd_write_number(2,4,minute);	
			Lcd_write_number(2,7,second);

			while(3 == timeOption && timeSetkey)
			{
				Lcd_write_number(2,7,second);
				Delayms(1000);
				Lcd_write_string(0xc6,"  ");
				Delayms(1000);
				Lcd_write_number(2,7,second);
				checky_sellect();
				checky_sub();
				checky_add();
				checky_timeSet();

			}
			while(2 == timeOption && timeSetkey)
			{
				Lcd_write_number(2,4,minute);
				Delayms(1000);
				Lcd_write_string(0xc3,"  ");
				Delayms(1000);
				Lcd_write_number(2,4,minute);	
				checky_sellect();
				checky_sub();
				checky_add();
				checky_timeSet();
			
			}
			while(1 == timeOption && timeSetkey)
			{
				Lcd_write_number(2,1,hours);
				Delayms(1000);
				Lcd_write_string(0xc0,"  ");
				Delayms(1000);
				Lcd_write_number(2,1,hours);
				checky_sellect();
				checky_sub();
				checky_add();
				checky_timeSet();
		
			}

			
	
		}
		
		//���set��ʾ
		Lcd_write_string(0x8d,"   ");
		
		DS1302_WriteByte(0x80,second/10*16 + second%10);
		//����
		DS1302_WriteByte(0x82,minute/10*16 + minute%10);
		//Сʱ
		DS1302_WriteByte(0x84,hours/10*16 + hours%10);
		//�� ���� Сʱ ����ˢ��
		Lcd_write_number(2,7,DS1302_ReadByte(0x81));
		Lcd_write_number(2,4,DS1302_ReadByte(0x83));
		Lcd_write_number(2,1,DS1302_ReadByte(0x85));
		second = DS1302_ReadByte(0x81);
		minute = DS1302_ReadByte(0x83);
		hours = DS1302_ReadByte(0x85);
		
	}
	
	
	return 0;
}