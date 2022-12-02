#include <REGX52.H>




sbit intoTimeSet = P3^1;
//设置秒或者分或者小时
sbit sellect = P3^0;
sbit timeAdd = P3^2;
sbit timesub = P3^3;

//用来进入Set的判断依据
bit timeSetkey = 0;


//检查按键是否按下进入时间设置模式
void checky_timeSet()
{
	if(!intoTimeSet)
	{
		Delayms(10);
		if(!intoTimeSet)
		{
			Delayms(1000);
			timeSetkey = ~timeSetkey;
		}
	}
}

void checky_sellect()
{
	if(!sellect)
	{
		Delayms(10);
		if(!sellect)
		{
			Delayms(10);
			timeOption += 1;
			if(4 == timeOption)
			{
				timeOption = 1;
			}
			
		}
	}
}

void checky_add()
{
	if(!timeAdd)
	{
		Delayms(10);
		if(!timeAdd)
		{
			Delayms(10);
			if(1 == timeOption)
			{
				hours++;
			}
			else if(2 == timeOption)
			{
				minute++;
			}
			else if(3 == timeOption)
			{
				second++;
			}
		
			
		}
	}
}

void checky_sub()
{
	if(!timesub)
	{
		Delayms(10);
		if(!timesub)
		{
			Delayms(10);
			if(1 == timeOption)
			{
				hours--;
			}
			else if(2 == timeOption)
			{
				minute--;
			}
			else if(3 == timeOption)
			{
				second--;
			}
		
			
		}
	}
}