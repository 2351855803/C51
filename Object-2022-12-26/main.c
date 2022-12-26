#include <REGX52.H>
#include "DHT11.h"
#include "Delay.h"
#include "LCD1602.h"
#include "UART.h"
#include "Timer0.h"
#include "Key.h"

//���
sbit Motor = P1^0;



////���붨ʱ������
//unsigned char Timer_count = 0;
//�������
unsigned char Motor_count = 0;
//�ж���˸
//static unsigned char flag = 1;
//unsigned char flag2 = 0;
//���PWM
static char compare = 0;





int main()
{
	unsigned char i = 70;
	unsigned char i2 = 16;

	//DHT11�ϵ������Ҫ��ʱ1s
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
		//����ĳ��ֵ���ת��
		compare = DHT11_Alarm(&i,&i2);
		
		//��δ�����쳣�����ֹͣ
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
	//��λ��ʱ��
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
}