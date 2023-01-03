#include <REGX52.H>

//_nop_()会用到下面头文件，代表跳过一个机器周期，12Mhz为1us，11.0592Mhz约为1.08us
#include <intrins.h>


unsigned char zhengZhuan[8]={0xf2,0xf6,0xf4,0xfc,0xf8,0xf9,0xf1,0xf3}; 

unsigned char fanZhuan[8]={0xf1,0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3}; 

//设置A B C的吃药次数和用量
//数组分别存储 A吃药次数 A用量 B吃药次数 B用量  C吃药次数 C用量  以及用药间隔
unsigned char User[6] = 0;
//User数组的下标
//static表示静态，不会随着函数结束而使得该变量清零
static unsigned char num = 0;


//从0-5 分别为 A的小时分钟 B的小时分钟 C的小时分钟
char ABC_setTime[7] = 0;
//ABC_setTime数组的下标
unsigned char set_timeI = 0;

//定义时钟变量
char hour = 0;
char minute = 0;
char second = 0;

//定时器0计数
static unsigned int timer0_count = 0;


//定义lcd1602寄存器
#define Lcdout P0

//用来判断温度有没有大于35
unsigned char tempFlag = 0;
//LCD1602定义引脚
sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;

//用药的灯
sbit A_LED = P2^0;
sbit B_LED = P2^1;
sbit C_LED = P2^2;

//打开 关闭药柜
sbit Motor_open = P1^6;
sbit Motor_off = P1^7;

//DS18B20
sbit DSPORT=P1^5;



//*********************************************************************************************************************************************

 /**
  *@brief		  延时函数子函数
  *@param	
  *@return
 */
void Delayms(unsigned char mm)	//需要延时多少ms就输入多少
{
	
	while(mm--)
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);		
	}		

}

void Delay1ms(unsigned int n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}

void delay5(unsigned char n)
{
	do{_nop_();
	  	_nop_();
		_nop_();
		n--;
	  }
	  while(n);
}
//*********************************************************************************************************************************************
 /**
  *@brief		  DS18B20
  *@param	
  *@return
 */
unsigned char Ds18b20Init()
{
	unsigned char i;
	DSPORT=0;
	delay5(120);
	DSPORT=1;
	i=0;
	while(DSPORT)
	{
		Delay1ms(1);
		i++;
		if(i>5)
		return 0;
	}
	return 1;
}
unsigned char Ds18b20WriteByte(unsigned char dat)
{
	unsigned int i,j;
	for (j=0;j<8;j++)
	{
		DSPORT=0;
		i++;
		DSPORT=dat&0x01;
		delay5(12);
		DSPORT=1;
		dat>>=1;
	}
	return dat;
}
unsigned char Ds18b20ReadByte()
{
	unsigned char byte,bi,i,j;
	for(j=8;j>0;j--)
	{
		DSPORT=0;
		i++;
		DSPORT=1;
		i++;
		i++;
		bi=DSPORT;
		byte=(byte>>1)|(bi<<7);
		delay5(9);
	}
	return byte;
}
void Ds18b20ReadTempCom()
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);
	Ds18b20WriteByte(0x44);
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);
	Ds18b20WriteByte(0xbe);
}

int Ds18b20ReadTemp()
{
	int temp=0;
	unsigned char tmh,tml;
	Ds18b20ReadTempCom();
	tml= Ds18b20ReadByte();
	tmh= Ds18b20ReadByte();
	temp=tmh;
	temp<<=8;
	temp|=tml;
	return temp;
}

//*********************************************************************************************************************************************
 /**
  *@brief		  以下为LCD1602子函数
  *@param	
  *@return
 */                                              


//发送命令  RS = 0
void Write_cmd(unsigned char cmd)
{

	RS = 0;
	RW = 0;
	EN = 0;

	//单片机把要发送的数据放到数据总线里
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);

	
}
void Write_data(unsigned char cmd)
{

	RS = 1;
	RW = 0;
	EN = 0;

	//单片机把要发送的数据放到数据总线里
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);
	

}
void Lcd_initial()
{

	Write_cmd(0x01);
	Write_cmd(0x06);
	
	Write_cmd(0x0c);
	Write_cmd(0x38);
	

	
	Delayms(1);
	
	
}

void Lcd_write_string(char cmd, char* addr)
{
	while(*addr != '\0')
	{
		Write_cmd(cmd++);
		Write_data(*addr);
		addr++;
	}
}



//在第几行第几列显示数字
//形参列表（行，列，数字）

void Lcd_write_number(char line, char row ,unsigned int number)
{
	if(1 == line)
	{
		Write_cmd(0x80+row-1);
		Write_data((number/10)+0x30);
		Write_data((number%10)+0x30);
	}
	else if(2 == line)
	{
		Write_cmd(0xc0+row-1);
		Write_data((number/10)+0x30);
		Write_data((number%10)+0x30);
	}
}


//*********************************************************************************************************************************************
/**
  *@brief		矩阵键盘函数
  *@param	
  *@return
 */
//检测按下
unsigned char Matrix_key()
{
	unsigned char n = 0;
	unsigned char m = 0;
	P3=0xf0;
	
	//检测到有按键按下，高四位会有一个变成0
	if((P3&0xf0)!=0xf0);
	{
		Delayms(10);
			
		if((P3&0xf0)!=0xf0);
		{
			//取高四位
			n=P3&0xf0;
			
			P3=0x0f;

			//取低四位
			m=P3&0x0f;
			
			return(n+m);
		}
	}
}	
//通过矩阵键盘按下返回值
unsigned char Matrix_keyReturn()
{
	unsigned char temp;
	
	switch(Matrix_key())
	{
		case 0xee: temp = 1; break;
		case 0xde: temp = 2; break;
		case 0xbe: temp = 3; break;
		case 0x7e: temp = 4; break;
		case 0xed: temp = 5; break;
		case 0xdd: temp = 6; break;
		case 0xbd: temp = 7; break;
		case 0x7d: temp = 8; break;
		case 0xeb: temp = 9; break;
		case 0xdb: temp = 0; break;
//		case 0xbb: temp =11; break;
//		case 0x7b: temp =12; break;
//		case 0xe7: temp =12; break;
//		case 0xd7: temp =12; break;
//		case 0xb7: temp =12; break;
//		case 0x77: temp =12; break;
		
		
	}
	
	return temp;
}

//*********************************************************************************************************************************************
/**
  *@brief		ABC设置
  *@param	
  *@return
 */
//限制ABC用量
void ABC_Limit()
{
	User[0] %= 4;
	User[2] %= 4;
	User[4] %= 4;
	User[1] %= 10;
	User[3] %= 10;
	User[5] %= 10;
}
//设置ABC的量
void A_B_C_Set()
{
	
	if(0xe7 == Matrix_key())
	{
		User[num]++;
		while(0xe7 == Matrix_key());
	}else if(0xd7 == Matrix_key())
	{
		User[num]--;
		while(0xd7 == Matrix_key());
	}else if(0xb7 == Matrix_key())
	{
		num++;
		if(num > 5) {num = 0;}
		while(0xb7 == Matrix_key());
	}
	ABC_Limit();
	Write_cmd(0xc1);
	Write_data(':');
	Write_data(User[0]+0x30);
	Write_data(User[1]+0x30);
	Write_cmd(0xc5);
	Write_data(':');
	Write_data(User[2]+0x30);
	Write_data(User[3]+0x30);
	Write_cmd(0xc9);
	Write_data(':');
	Write_data(User[4]+0x30);
	Write_data(User[5]+0x30);
	Write_cmd(0xcd);
	Write_data((num+1)+0x30);
	

	
}

//设置ABC用药时间的小时分钟限制
void ABCTime_Judge()
{
	unsigned char i = 0;
	for(i = 0; i <=5; i+=2)
	{
		if(ABC_setTime[i] >= 24)
		{
			ABC_setTime[i] = 0;
		}else if(ABC_setTime[i] < 0)
		{
			ABC_setTime[i] = 23;
		}
	}
	
	for(i = 1; i <= 5; i+=2)
	{
		if(ABC_setTime[i] >= 60)
		{
			ABC_setTime[i] = 0;
		}else if(ABC_setTime[i] < 0)
		{
			ABC_setTime[i] = 59;
		}
	}
	
	
}

//设置ABC用药时间
void ABC_SetEatTime()
{
	while(Matrix_key() != 0x77)
	{
		//检查时间是否合法
		ABCTime_Judge();
		
		//如果用药间隔小于4h
		if(ABC_setTime[6] < 4)
		{
			Lcd_write_string(0x8d,"!");
		}else 
		{
			Lcd_write_string(0x8d," ");
	
		}
		//服药间隔小于24
		ABC_setTime[6] %= 25;
		if(ABC_setTime[6] < 0) {ABC_setTime[6] = 23;}
		
		//设置ABC用药时间
		Lcd_write_string(0x80,"Set:");
		Lcd_write_string(0xC0,"A");
		Lcd_write_number(2,2,ABC_setTime[0]);
		Lcd_write_string(0xC3,":");
		Lcd_write_number(2,5,ABC_setTime[1]);
			
		Lcd_write_string(0x87,"B");
		Lcd_write_number(1,9,ABC_setTime[2]);
		Lcd_write_string(0x8a,":");
		Lcd_write_number(1,12,ABC_setTime[3]);
			
		Lcd_write_string(0xc7,"C");
		Lcd_write_number(2,9,ABC_setTime[4]);
		Lcd_write_string(0xca,":");
		Lcd_write_number(2,12,ABC_setTime[5]);
		
		//设置间隔
		Lcd_write_number(1,15,ABC_setTime[6]);	
		if(0xe7 == Matrix_key())
		{
			ABC_setTime[set_timeI]++;
			while(0xe7 == Matrix_key());
		}else if(0xd7 == Matrix_key())
		{
			ABC_setTime[set_timeI]--;
			while(0xd7 == Matrix_key());
		}else if(0xb7 == Matrix_key())
		{
			set_timeI++;
			if(set_timeI > 6) {set_timeI = 0;}
			while(0xb7 == Matrix_key());
		}	
		
		//显示下标
		Lcd_write_number(1,5,(set_timeI+1));
	}
	//清屏
	Write_cmd(0x01);
	//延时防止把后面需要的也清屏了
	Delayms(10);
	
}


//到时间后ABC的灯亮并且提醒
unsigned char ABC_Warn()
{
	//吃A药
	if(hour == ABC_setTime[0] && minute == ABC_setTime[1])
	{
		//亮灯
		A_LED = 0; B_LED = 1; C_LED = 1;

		//LCD显示
		Lcd_write_string(0x8a,"A");
		return 1;
	}else if(hour == ABC_setTime[2] && minute == ABC_setTime[3])
	{
		//吃B药
		//亮灯
		A_LED = 1; B_LED = 0; C_LED = 1;
		//LCD显示
		Lcd_write_string(0x8a,"B");
		return 1;
		
	}else if(hour == ABC_setTime[4] && minute == ABC_setTime[5])
	{
		//吃C药
		//亮灯
		A_LED = 1; B_LED = 1; C_LED = 0;
		//LCD显示
		Lcd_write_string(0x8a,"C");
		return 1;
		
	}
	return 0;
}
//*********************************************************************************************************************************************

/**
  *@brief		定时器0初始化
  *@param	
  *@return
 */
void Timer0_Init()
{
	//打开定时器0的1模式
	TMOD &= 0xf0;
	TMOD |= 0x01;
	
	//设置TCON
	TF0 = 0;
	TR0 = 1;
	
	//设置计时时间
	//这里设置10000 == 10000us == 10ms == 0.01s
	//TH0和TL0为八位，分别把一个十六位的高八位低八位赋值
	TH0 = (65535 - 10000)/256;
	TL0 = (65535 - 10000)%256;
	
	//打开中断
	ET0 = 1;
	//总中断
	EA = 1;
}

//时钟判断函数
void Time_Judge()
{
	if(second >= 60)
	{
		minute++;
		second = 0;
	}else if(minute >= 60)
	{
		hour++;
		minute = 0;
	}else if(hour >= 24)
	{
		hour = 0;
	}else if(minute < 0)
	{
		minute = 59;
		hour--;
	}else if(hour < 0)
	{
		hour = 23;
	}
}

//时钟显示函数
void Time_Show()
{
	Time_Judge();
	Lcd_write_string(0X82,":");
	Lcd_write_number(1,1,hour);
	Lcd_write_number(1,4,minute);

}

//操作时钟
void Time_Set()
{
	//分加
	if(0xbb == Matrix_key())
	{
		Delayms(10);
		if(0xbb == Matrix_key())
		{
			minute += 5;
			while(0xbb == Matrix_key());
		}
	}
	//分减
	if(0x7b == Matrix_key())
	{
		Delayms(10);
		if(0x7b == Matrix_key())
		{
			minute --;
			while(0x7b == Matrix_key());
		}
	}
}

//*********************************************************************************************************************************************
/**
  *@brief		 电机键盘函数
  *@param	
  *@return
 */
void Motor()
{
	unsigned char i = 0;
	unsigned char j = 0;
	if(0 == Motor_open && 0 == tempFlag && ABC_Warn())
	{
		Delayms(10);
		if(0 == Motor_open)
		{
			for(i = 0; i < 8; i++)
			{
				P1 = zhengZhuan[i];
				Delayms(100);
					
			}
		}
		

	}else if(0 == Motor_off && 0 == tempFlag && ABC_Warn())
	{
		Delayms(10);
		if(0 == Motor_off)
		{
			for(i = 0; i < 8; i++)
			{
				P1 = fanZhuan[i];
				Delayms(100);
					
			}
		}		
	}

}



//*********************************************************************************************************************************************
//*********************************************************************************************************************************************
//*********************************************************************************************************************************************

void main()
{

	//接受温度
	unsigned int tmp;
	//LCD1602初始化
	Lcd_initial();
	//定时器0初始化
	Timer0_Init();

	//显示学号后两位
	Lcd_write_string(0xce,"47");
	
	
	//设置ABC的吃药时间，设置完后，吃药的时间会存储在数组中
	ABC_SetEatTime();
	
	
	//设置A用量
	Lcd_write_string(0xc0,"A");
	Lcd_write_string(0xc4,"B");
	Lcd_write_string(0xc8,"C");
	
	//显示学号后两位
	Lcd_write_string(0xce,"47");

	
	
	
	
	
	
	while(1)
	{
		//接受温度
		//为什么/16 是因为ds18b20由十六位组成，然后低四位储存的是小数，导致实际温度比返回值小2的四次方，所以要除16
		tmp = (Ds18b20ReadTemp()/16);
		
		//判断体温有没有大于35
		if(tmp > 35) {tempFlag = 1;}
		else {tempFlag = 0;}
		if(tempFlag) {Lcd_write_string(0xcc,"!");}
		else {Lcd_write_string(0xcc," ");}
		
		//步进电机
		Motor();
		
		//LCD显示温度
		Lcd_write_string(0x86,"T");
		Lcd_write_number(1,8,tmp);

		//时钟显示 设置 ABC设置
		Time_Show();
		Time_Set();
		A_B_C_Set();
		//到达设定的吃药时间
		ABC_Warn();

	}
	
	
	
	
}


//定义定时器0中断
void Timer0_Routine() interrupt 1
{
	timer0_count++;
//	timer0_count == 100表示过去1s
	if( 100 == timer0_count)
	{
		second++;
		timer0_count = 0;
	}
	//复位
	TH0 = (65535 - 10000)/256;
	TL0 = (65535 - 10000)%256;
}