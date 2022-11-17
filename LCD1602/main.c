#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"


int main()
{
	int i = 0;
	char arr[] = "abcdef";
	
	
	//≥ı ºªØ
	Lcd_initial();
	
	while(1)
	{
		while(arr[i] != '\0')
		{
			Delayms(500);
			Write_cmd(0x80+i);
			Write_data(arr[i]);
			i++;
				
		}

	}
	
	return 0;
}