#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "DHT11.h"

int main()
{
	unsigned char arr[5];
	Delayms(500); Delayms(500); Delayms(500);
	
	Lcd_initial();
	
	while(1)
	{
		DHT11_Read_5_Byte(arr);
		//Êª¶È
		Lcd_write_number(1,1,arr[0]);
		//ÎÂ¶È
		Lcd_write_number(2,1,arr[2]);
		
		Delay1000ms();
	}
	
	
	return 0;
}