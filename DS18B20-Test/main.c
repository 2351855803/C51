#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"

int main()
{
	
	Lcd_initial();
	
	while(1)
	{
		DS18B20_ReverseT();
		Lcd_write_number(2,1,DS18B20_ReadT());
		Lcd_write_string(0xc3,".");
		Lcd_write_number(2,5,((unsigned long)(DS18B20_ReadT()*10000))%10000);
	}
	
	return 0;
}