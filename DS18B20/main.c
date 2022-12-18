#include <REGX52.H>
#include "OneWire.h"
#include "LCD1602.h"
#include "DS18B20.h"

int main()
{
	unsigned char Max = 26;
	unsigned char Min = 21;
	Lcd_initial();

	while(1)
	{
		DS18B20_ConvertT();
		Lcd_write_number(2,1,DS18B20_ReadT());
		Lcd_write_string(0xc3,".");
		Lcd_write_number(2,5,((unsigned long)(DS18B20_ReadT()*10000))%10000);
		
		
		if(DS18B20_ReadT() > Max)
		{
			Lcd_write_string(0x80,"High!");
		}
		else if (DS18B20_ReadT() < Min)
		{
			Lcd_write_string(0x80,"Low!");
		}
		else
		{
			Lcd_write_string(0x80,"     ");
		}
		
	}
	
	
	return 0;
}