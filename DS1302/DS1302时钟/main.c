#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"

unsigned char second;
unsigned char minute;
unsigned char hours;

int main()
{
	//LCD1602初始化
	Lcd_initial();
	//DS1302初始化
	DS1302_Init();
	
	//解除写保护
	DS1302_WriteByte(0x8e,0x00);
	
	Lcd_write_string(0x82,":");
	Lcd_write_string(0x85,":");
	
	//十六进制
	//写命令和数据（16进制）
	DS1302_WriteByte(0x80,89);
	DS1302_WriteByte(0x82,12);
	DS1302_WriteByte(0x84,16);
	while(1)
	{
		
		Lcd_write_number(1,7,DS1302_ReadByte(0x81));
		Lcd_write_number(1,4,DS1302_ReadByte(0x83));
		Lcd_write_number(1,1,DS1302_ReadByte(0x85));
	}
	
	
	return 0;
}