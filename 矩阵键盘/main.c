#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

//������������
char mycode[] = "2233";
char arr[4] = {0};


//------------------------------------------------------------ �ж��������ַ�
int judge(char* arr1, char* arr2)
{
	
	while(*arr2 != '\0')
	{
		if(*arr1++ != *arr2++)
		{
			return 0;
		}
	}
	
	return 1;
}


//------------------------------------------------------------
int main()
{
	//�ж�������ʾλ��
	int num = 0;
	int i;
	
	//lcd��ʼ��
	Lcd_initial();
	
	//��ʼ��ʾ0000
	Lcd_write_string(0x80,"0000");
	
	//��ʾ��������
	Lcd_write_string(0xc3,"EntryCode");
	
	while(1)
	{
			
		switch(Matrix_key())
		{
			case 0x77:
				Write_cmd(0x80+num); Write_data('1'); Delayms(200); arr[num] = '1'; num++;
				break;
			case 0x7b:
				Write_cmd(0x80+num); Write_data('2'); Delayms(200); arr[num] = '2'; num++;
				break;
			case 0x7d:
				Write_cmd(0x80+num); Write_data('3'); Delayms(200); arr[num] = '3'; num++;
				break;
			case 0x7e:
				Write_cmd(0x80+num); Write_data('4'); Delayms(200); arr[num] = '4'; num++;
				break;
	
		}
		

		

		//��λ��¼����λ��
		if(4 == num)
		{
			i = judge(arr,mycode);
			if(1 == i)
			{
				Lcd_write_string(0xce,"OK");
			}
			else
			{
				Lcd_write_string(0x8d,"ERR");
			}

		
			num = 0;
		}
		
		
	}

	
	
	
	return 0;
}