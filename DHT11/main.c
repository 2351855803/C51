#include <REGX52.H>
#include "LCD1602.h"
#include "DHT11.h"
#include "Delay.h"
#include "UART.h"

unsigned char temH, temL, humiH, humiL;


int main()
{
	
	Lcd_initial();
	Lcd_write_string(0x80,"tmp:");
	Lcd_write_string(0xc0,"hum:");

	while(1)
	{
		
		DHT11_Read_5Byte(&temH, &temL, &humiH, &humiL);
		Lcd_write_number(1,5,temH);
		Lcd_write_number(2,5,humiH);

		Delayms(1000);
	}
	
	
	
	return 0;
}