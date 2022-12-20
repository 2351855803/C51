#include <REGX52.H>
#include "Timer1.h"

sbit Motor = P1^0;
int count = 0;
int compare = 0;

int main()
{
	
	Timer0_Init();
	while(1)
	{
		if(P3_1 == 0) {compare = 1;}
		if(P3_0 == 0) {compare = 3;}
		if(P3_2 == 0) {compare = 6;}
		if(P3_3 == 0) {compare = 9;}
	}
	
	
	return 0;
}


void Timer0Routine() interrupt 1
{

	
	
	if(count < compare)
	{
		
		Motor = 1;

	}
	else if(count >= compare)
	{
		Motor = 0;

	}
	
	count++;
	count %= 10;
	
	TH0 = (65535-100);
	TL0 = (65535-100);
	


}