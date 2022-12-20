#include <REGX52.H>
#include "Delay.h"



sbit LED = P2^0;


int main()
{
	char time_on = 10;
	unsigned char i = 0;
	while(1)
	{
	
		for(time_on = 0; time_on <= 10; time_on++ )
		{
			for(i = 0; i < 30; i++)
			{
				LED = 0;
				Delayms(time_on);
				LED = 1;
				Delayms(10 - time_on);
			}
			
		}
		for(time_on = 10; time_on >= 0; time_on-- )
		{
			for(i = 0; i < 30; i++)
			{
				LED = 0;
				Delayms(time_on);
				LED = 1;
				Delayms(10 - time_on);
			}
			
		}
		

		
	}
	
	
	return 0;
}