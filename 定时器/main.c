#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"




//**************************************************************

//1. �Ĵ�������ģʽTMOD
//2. ���ƼĴ���TCON
//3. TH0 TL0

// 65536us == 65ms == 0.065s
//**************************************************************


int main()
{
	T0_Initial();
	while(1)
	{
		
	}
	
	
	return 0;
}



//��ʱ��0�ж�
//�������
int count = 0;

void T0_Routine() interrupt 1
{
	count++;
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	
	if(100 == count)
	{
		count = 0;
		P2_0 = ~P2_0;
	}
	


}









