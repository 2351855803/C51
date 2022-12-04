#include <REGX52.H>
#include "AT24C02.h"
#include "LCD1602.h"
#include "Delay.h"

int main()
{
	unsigned char i;
	Lcd_initial();
	AT24C02_Write(1,i++);
	Delayms(5);
	Delayms(500);

	while(1)
	{
		
		Lcd_write_number(2,1,AT24C02_Read(1));
		
	}
	
	
	return 0;
}