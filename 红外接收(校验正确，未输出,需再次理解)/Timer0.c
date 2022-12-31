//�õ���ʱ���������˶��ٸ���
#include <REGX52.H>

//��ʼ�����ǲ�����ʱ��
void Timer0_Init()
{
	TMOD &= 0xf0;
	TMOD |= 0X01;
	TH0 = 0/256;
	TL0 = 0%256;
	TF0 = 0;
	TR0 = 0;

		
}



//����ʱ��������ֵ
void Timer_Set(unsigned int num)
{
	TH0 = num / 256;
	TL0 = num % 256;
}


//����ʱ��
void Timer_Begain(unsigned char flag)
{
	TR0 = flag;	
}


//����
unsigned int Timer_Count()
{

	return (TH0 << 8) | TL0;
}






