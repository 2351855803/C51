#include <REGX52.H>
#include "DHT11.h"
#include "Delay.h"
#include "LCD1602.h"
#include "UART.h"
#include "Timer0.h"
#include "Key.h"
#include "AT24C02.h"

//电机
sbit Motor = P3^7;



////进入定时器计数
//unsigned char Timer_count = 0;
//电机计数
char Motor_count = 0;
//判断闪烁
//static unsigned char flag = 1;
//unsigned char flag2 = 0;
//电机PWM
static char compare = 0;

//警戒值
unsigned char humHWarn;
unsigned char humLWarn;
unsigned char tmpHWarn;
unsigned char tmpLWarn;


int main()
{


	//DHT11上电后至少要延时1s
	Delayms(1500);
	
	//初始化
	Lcd_initial();
	Timer0_Init();
	UART_Init();
	
	//把保存的警戒值赋值进去
	DHT11_SaveDH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);

	
	
	//显示进去的界面
	LCD_ShowBegin();
	//设置上下限
	LCD_ShowSetTH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);
	compare = DHT11_H_Alarm(&humHWarn,&tmpHWarn);
	//电机标志位清零
	Motor = 0;
	
	
	while(1)
	{
		

		DHT11_LCD1602_Show();
		
		//设置按键进入
		if(0x77 == Matrix_key()) {while(0x77 == Matrix_key()); LCD_ShowSetTH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);}
		
		//超过某个值电机转动
		//温湿度高操作
		compare = DHT11_H_Alarm(&humHWarn,&tmpHWarn);
		//温湿度低操作
		DHT11_L_Alarm(&humLWarn,&tmpLWarn);
		
		//当未出现异常，电机停止
		if(0 == compare) {Motor = 0;}
		
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