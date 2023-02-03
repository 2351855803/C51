#include "intrins.h"
void Delayms(unsigned char mm)		//@12.000MHz
{
	
	while(mm--)
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);		
	}
}


void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 36;
	j = 217;
	do
	{
		while (--j);
	} while (--i);
}


void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	i = 11;
	while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
	while (--i);
}

void Delay40us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 15;
	while (--i);
}

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

