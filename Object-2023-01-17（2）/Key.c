#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "AT24C02.h"

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

/**
  *@brief	通过矩阵键盘来设置温度湿度上下限
  *@param	分别是 湿度上限 湿度下线 温度上限 温度下线
  *@return  void
 */
void Matrix_Set_DH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	//湿度上下限加减
	if(0x77 == Matrix_key()) {(*humHWarn)++; AT24C02_Write(1,(*humHWarn)); while(0x77 == Matrix_key());}
	if(0x7b == Matrix_key()) {(*humHWarn)--; AT24C02_Write(1,(*humHWarn)); while(0x7b == Matrix_key());}
	if(0x7d == Matrix_key()) {(*humLWarn)++; AT24C02_Write(2,(*humLWarn)); while(0x7d == Matrix_key());}
	if(0x7e == Matrix_key()) {(*humLWarn)--; AT24C02_Write(2,(*humLWarn)); while(0x7e == Matrix_key());}
	
	//温度上下限加减
	if(0xb7 == Matrix_key()) {(*tmpHWarn)++; AT24C02_Write(3,(*tmpHWarn)); while(0xb7 == Matrix_key());}
	if(0xbb == Matrix_key()) {(*tmpHWarn)--; AT24C02_Write(3,(*tmpHWarn)); while(0xbb == Matrix_key());}
	if(0xbd == Matrix_key()) {(*tmpLWarn)++; AT24C02_Write(4,(*tmpLWarn)); while(0xbd == Matrix_key());}
	if(0xbe == Matrix_key()) {(*tmpLWarn)--; AT24C02_Write(4,(*tmpLWarn)); while(0xbe == Matrix_key());}
	

}










