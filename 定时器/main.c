#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "LCD1602.h"




//**************************************************************

//1. 寄存器工作模式TMOD
//2. 控制寄存器TCON
//3. TH0 TL0

// 65536us == 65ms == 0.065s
//**************************************************************

//定义 时 分 秒
static unsigned char hour = 0;
static unsigned char minute = 0;
static unsigned char second = 0;



void Time_check()
{
	if(60 == second)
	{
		minute++;
		second = 0;
	}
	if(60 == minute)
	{
		hour++;
		second = 0;
	}
	if(24 == hour)
	{
		hour = 0;
	}
}





int main()
{
	

	//默认0.1s进一次中断
	T0_Initial();
	//初始化
	Lcd_initial();
	

	//初始化闹钟
	Lcd_write_string(0xc0,"00:00:00");
	Lcd_write_string(0x80,"NowTime:");
	while(1)
	{
		
		Lcd_write_number(2,7,second);
		Lcd_write_number(2,4,minute);
		Lcd_write_number(2,1,hour);
		Time_check();

		
	}
	
	
	return 0;
}



//定时器0中断
//定义计数
static int count = 0;

void T0_Routine() interrupt 1
{
	//进入一次加一，每0.01s进入一次
	count++;
	
	//重新复位TH0 TL0
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	
	
	if(100 == count)
	{
		//清零
		count = 0;
		second++;		
	
	}


}









