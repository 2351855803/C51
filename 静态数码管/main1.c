#include <REGX52.H>
#include <intrins.h>


//�����������
char arr[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

//��ʱ500ms
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




void temp(int num , int num1)
{
	//ͨ������ת�������Ƹ�Ƭѡ
	P2_2 = num%2;
	num /= 2;
	P2_3 = num%2;
	num /= 2;
	P2_4 = num%2;

	P0 = arr[num1];	
	
}


int main()
{
	//------------------------------------------  ѭ����ʾ
	//��ʱ���Ժ���,�β��б��ڼ�������������������֣�
	//����ܷ�Χ 0-7
	//���Ը���0.5s��ʾ
//	while(1)
//	{
//		int i;
//		for(i = 0; i <= 7; i++)
//		{
//			Delay500ms();
//			temp(i,7);
//			
//		}		
//	}
	
	
	//------------------------------------------  ��̬��ʾ0-9�����0.5s
	
	while(1)
	{
		int i;
		for(i = 0; i <= 7; i++)
		{
			Delay500ms();
			temp(i,i);
			
		}		
	}
	
	return 0;
}




