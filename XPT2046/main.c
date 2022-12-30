#include <REGX52.H>
#include "LCD1602.h"
#include "XPT2046.h"
#include "Delay.h"

int main()
{
	
	Lcd_initial();
	
	while(1)
	{
		//电阻
		Lcd_write_number(2,1,XPT2046_Read(0x9c));
		Delayms(10);
		//热敏电阻
		Lcd_write_number(2,6,XPT2046_Read(0xdc));
		Delayms(10);
		//光敏电阻
		Lcd_write_number(2,10,XPT2046_Read(0xac));
		Delayms(10);
	}
	
	
	
	
	
	
	return 0;
}