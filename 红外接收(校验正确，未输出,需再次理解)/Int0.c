#include <REGX52.H>




/**
  *@brief	�ⲿ�ж�0��ʼ��
  *@param	void
  *@return	void
 */
void Int0_Init()
{
	IT0 = 1;
	IE0 = 0;
	EX0 = 1;
	EA = 1;
	PX0 = 1;
}


//�ж�ģ��
//void Int0_Routine() interrupt 0
//{

//}