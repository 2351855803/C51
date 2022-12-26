#include <REGX52.H>
#include "DHT11.h"
#include "Delay.h"
#include "LCD1602.h"
#include "UART.h"
#include "Timer0.h"
#include "Key.h"

//电机
sbit Motor = P1^0;



////进入定时器计数
//unsigned char Timer_count = 0;
//电机计数
unsigned char Motor_count = 0;
//判断闪烁
//static unsigned char flag = 1;
//unsigned char flag2 = 0;
//电机PWM
static char compare = 0;





int main()
{
	unsigned char i = 70;
	unsigned char i2 = 16;

	//DHT11上电后至少要延时1s
	Delayms(1500);
	
	Lcd_initial();
	Timer0_Init();
	UART_Init();
	
	Motor = 0;
	
	while(1)
	{
		
		//DHT11_Read_5_Byte(arr);
		DHT11_LCD1602_Show();
		Lcd_write_number(2,9,Matrix_key_Read());
		//超过某个值电机转动
		compare = DHT11_Alarm(&i,&i2);
		
		//当未出现异常，电机停止
		if(!compare) {Motor = 0;}
		
	}
	
	
	
	return 0;
}


void Timer_Routine() interrupt 1
{
	

	if(Motor_count < compare)
	{
		
		Motor = 1;
	}else if
	(Motor_count >= compare)
	{
		Motor = 0;

	}
	Motor_count++;
	Motor_count %= 10;
	//复位定时器
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
}