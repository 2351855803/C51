#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"

/**
  *@brief	通过按键来选择模式
  *@param	
  *@return	按键代表的模式  
 */
unsigned char Matrix_key()
{
	unsigned char n,m;
	P1=0xf0;
	
	//检测到有按键按下，高四位会有一个变成0
	if((P1&0xf0)!=0xf0);
	{
		Delayms(10);
			
		if((P1&0xf0)!=0xf0);
		{
			//取高四位
			n=P1&0xf0;
			
			P1=0x0f;

			//取低四位
			m=P1&0x0f;
			
			return(n+m);
		}
	}
}


unsigned char Matrix_key_Read()
{
	switch(Matrix_key())
		{
			case 0x77:
				Write_cmd(0x8a); Write_data('1'); return 1;
				break;
			case 0x7b:
				Write_cmd(0x8a); Write_data('2'); return 2;
				break;
			case 0x7d:
				Write_cmd(0x8a); Write_data('3'); return 3;
				break;
			case 0x7e:
				Write_cmd(0x8a); Write_data('4'); return 4;
				break;
			
			case 0xb7:
				Write_cmd(0x8a); Write_data('5'); return 5;
				break;
			case 0xbb:
				Write_cmd(0x8a); Write_data('6'); return 6;
				break;
			case 0xbd:
				Write_cmd(0x8a); Write_data('7'); return 7;
				break;
			case 0xbe:
				Write_cmd(0x8a); Write_data('8'); return 8;
				break;
			
			case 0xd7:
				Write_cmd(0x8a); Write_data('9'); return 9;
				break;
			case 0xdb:
				Write_cmd(0x8a); Write_data('0'); return 0;
				break;
	
		}
		
}












