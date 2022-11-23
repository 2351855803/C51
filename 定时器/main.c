#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "LCD1602.h"




//**************************************************************

//1. �Ĵ�������ģʽTMOD
//2. ���ƼĴ���TCON
//3. TH0 TL0

// 65536us == 65ms == 0.065s
//**************************************************************

//���� ʱ �� ��
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
	

	//Ĭ��0.1s��һ���ж�
	T0_Initial();
	//��ʼ��
	Lcd_initial();
	

	//��ʼ������
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



//��ʱ��0�ж�
//�������
static int count = 0;

void T0_Routine() interrupt 1
{
	//����һ�μ�һ��ÿ0.01s����һ��
	count++;
	
	//���¸�λTH0 TL0
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	
	
	if(100 == count)
	{
		//����
		count = 0;
		second++;		
	
	}


}









