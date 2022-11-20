
#include <REGX52.H>
#include "Delay.h"

//矩阵键盘子函数
//逻辑是首先全部拉高，然后按列置为零，如果哪两个引脚均为0，则就是按下

		
//		     P1_3  P1_2  P1_1 P1_0
//		P1_7

//		P1_6

//		P1_5

//		P1_4

//P1_3到P1_0分别置零

//线反转法
//低位全部拉为0

unsigned char Matrix_key()
{
//	1111 0000
//	1011 0000
//	
//	n=P1&0xf0;
//	1011 0000
//	
//	P1=0x0f;
//	0000 1111
//	m=P1&0x0f;
	
	
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

//--------------------------------------------------------------------------------------

//	while(1)
//	{
//		//先全部拉高
//		P1 = 0xff;
//		
//		P1_3 = 0;
//		switch(P1)
//		{
//			case 0x77: 
//				Delayms(10); while(0x77 == P1); Delayms(10); return 1; break;
//			case 0xb7:
//				Delayms(10); while(0xb7 == P1); Delayms(10); return 5; break;
//			case 0xd7:
//				Delayms(10); while(0xd7 == P1); Delayms(10); return 9; break;
//			case 0xe7:
//				Delayms(10); while(0xe7 == P1); Delayms(10); return 13; break;
//		}
//		
//		P1 = 0xff;
//		P1_2 = 0;
//		switch(P1)
//		{
//			case 0x7b: 
//				Delayms(10); while(0x7b == P1); Delayms(10); return 2; break;
//			case 0xbb:
//				Delayms(10); while(0xbb == P1); Delayms(10); return 6; break;
//			case 0xdb:
//				Delayms(10); while(0xdb == P1); Delayms(10); return 10; break;
//			case 0xeb:
//				Delayms(10); while(0xeb == P1); Delayms(10); return 14; break;
//		}

//		P1 = 0xff;
//		P1_1 = 0;
//		switch(P1)
//		{
//			case 0x7d: 
//				Delayms(10); while(0x7d == P1); Delayms(10); return 3; break;
//			case 0xbd:
//				Delayms(10); while(0xbd == P1); Delayms(10); return 7; break;
//			case 0xdd:
//				Delayms(10); while(0xdd == P1); Delayms(10); return 11; break;
//			case 0xed:
//				Delayms(10); while(0xed == P1); Delayms(10); return 15; break;
//		}
//		
//		
//		P1 = 0xff;
//		P1_0 = 0;
//		switch(P1)
//		{
//			case 0x7e: 
//				Delayms(10); while(0x7e == P1); Delayms(10); return 4; break;
//			case 0xbe:
//				Delayms(10); while(0xbe == P1); Delayms(10); return 8; break;
//			case 0xde:
//				Delayms(10); while(0xde == P1); Delayms(10); return 12; break;
//			case 0xee:
//				Delayms(10); while(0xee == P1); Delayms(10); return 16; break;
//		}
//	}
}