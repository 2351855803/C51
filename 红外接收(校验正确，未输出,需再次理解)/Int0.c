#include <REGX52.H>




/**
  *@brief	外部中断0初始化
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


//中断模板
//void Int0_Routine() interrupt 0
//{

//}