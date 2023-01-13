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

//����ֵ
unsigned char humHWarn = 33;
unsigned char humLWarn;
unsigned char tmpHWarn = 55;
unsigned char tmpLWarn;


int main()
{


	//DHT11�ϵ������Ҫ��ʱ1s
	Delayms(1500);
	
	//��ʼ��
	Lcd_initial();
	Timer0_Init();
	UART_Init();
	
	//��ʾ��ȥ�Ľ���
	LCD_ShowBegin();
	//����������
	LCD_ShowSetTH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);
	
	//�����־λ����
	Motor = 0;
	
	while(1)
	{
		

		DHT11_LCD1602_Show();
		
		//���ð�������
		if(0x77 == Matrix_key()) {LCD_ShowSetTH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);}
		
		//����ĳ��ֵ���ת��
		compare = DHT11_H_Alarm(&humHWarn,&tmpHWarn);
		
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