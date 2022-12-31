//得到定时器计数记了多少个数
#include <REGX52.H>

//初始化但是不开定时器
void Timer0_Init()
{
	TMOD &= 0xf0;
	TMOD |= 0X01;
	TH0 = 0/256;
	TL0 = 0%256;
	TF0 = 0;
	TR0 = 0;

		
}



//给定时器计数赋值
void Timer_Set(unsigned int num)
{
	TH0 = num / 256;
	TL0 = num % 256;
}


//开定时器
void Timer_Begain(unsigned char flag)
{
	TR0 = flag;	
}


//计数
unsigned int Timer_Count()
{

	return (TH0 << 8) | TL0;
}






