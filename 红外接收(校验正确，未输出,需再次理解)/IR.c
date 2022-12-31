#include <REGX52.H>
#include "Int0.h"
#include "Timer0.h"


unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData;

unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;

unsigned char IR_Addres;
unsigned char IR_Command;


//初始化
void IR_Init()
{
	Timer0_Init();
	Int0_Init();
}




//外部中断0
void Int0_Routine() interrupt 0
{
	//空闲状态
	if(0 == IR_State)
	{
		
		Timer_Set(0);
		Timer_Begain(1);
		IR_State = 1;
		
	}
	else if(1 == IR_State)
	{
		
		IR_Time = Timer_Count();
		Timer_Set(0);
		//判断是start还是repeat
		if((IR_Time > ((13500) - 1500 )) && (IR_Time < ((13500) + 1500)))
		{
			//开始解码
			IR_State = 2;
			Timer_Set(0);
		}
		else if((IR_Time > ((11250) - 1500)) && (IR_Time < ((11250) + 1500)))
		{
			IR_RepeatFlag = 1;
			Timer_Begain(0);
			IR_State = 0;
		}
		else 
		{
			IR_State = 1;
		}
	}
	else if(2 == IR_State)
	{
		IR_Time = Timer_Count();
		Timer_Set(0);
		//0
		if(IR_Time > 1120 - 500 && IR_Time < 1120 + 500)
		{
			IR_Data[IR_pData/8] &= ~((0x01) << (IR_pData%8));
			IR_pData++;
		}
		else if(IR_Time > 2250 - 500 && IR_Time < 2250 + 500)
		{
			IR_Data[IR_pData/8] |= ((0x01) << (IR_pData%8));
			IR_pData++;
		}
		else 
		{
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData >= 32)
		{
			IR_pData = 0;
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))
			{
				IR_DataFlag = 1;
				IR_Addres = IR_Data[0];
				IR_Command = IR_Data[2];
				

			}
			Timer_Begain(0);
			IR_State = 0;
		}
		
	}

}







