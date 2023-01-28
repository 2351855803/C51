#include <REGX52.H>
#include "DHT11.h"
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "Key.h"
#include "AT24C02.h"
#include "SYN6288.h"
//���
/* ���Ŷ�����ʵ���в�� */
sbit Motor = P1^0;



////���붨ʱ������
//unsigned char Timer_count = 0;
//�������
char Motor_count = 0;
//�ж���˸
//static unsigned char flag = 1;
//unsigned char flag2 = 0;
//���PWM
static char compare = 0;

//����ֵ
unsigned char humHWarn;
unsigned char humLWarn;
unsigned char tmpHWarn;
unsigned char tmpLWarn;


int main()
{


	//DHT11�ϵ������Ҫ��ʱ1s
	Delayms(1500);
	
	//��ʼ��
	Lcd_initial();
	Timer0_Init();
	//����
	UART1_Init();
	//�ѱ���ľ���ֵ��ֵ��ȥ
	DHT11_SaveDH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);

	
	
	//��ʾ��ȥ�Ľ���
	LCD_ShowBegin();
	//����������
	LCD_ShowSetTH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);
	compare = DHT11_H_Alarm(&humHWarn,&tmpHWarn);
	//�����־λ����
	Motor = 0;
	
	
	while(1)
	{
		

		DHT11_LCD1602_Show();
		while( 0xee == Matrix_key())
		{
			DHT11_SynRead();
		}
		//���ð�������
		if(0x77 == Matrix_key()) {while(0x77 == Matrix_key()); LCD_ShowSetTH(&humHWarn,&humLWarn,&tmpHWarn,&tmpLWarn);}
		
		//����ĳ��ֵ���ת��
		//��ʪ�ȸ߲���
		compare = DHT11_H_Alarm(&humHWarn,&tmpHWarn);
		//��ʪ�ȵͲ���
		DHT11_L_Alarm(&humLWarn,&tmpLWarn);
		
		//��δ�����쳣�����ֹͣ
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
	//��λ��ʱ��
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
}

//����1�ж�
void Uart1_Isr() interrupt 4
{
	if(RI)
	{
		RI=0;
	}

}
