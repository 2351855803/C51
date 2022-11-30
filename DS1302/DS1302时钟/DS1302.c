#include <REGX52.H>


sbit DS1302_CE = P3^5;
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;


//*************************************************

//功能：DS1302初始化
//返回类型：void
//形参：void

//*************************************************
void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}




//*************************************************

//功能：DS1302写操作
//返回类型：void
//形参：unsigned char 命令 数据

//*************************************************
void DS1302_WriteByte(unsigned char cmd, byte)
{
	unsigned char i;
	
	//初始化后拉高
	DS1302_CE = 1;
	
	//从最低位到最高位分别获得命令
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = cmd & (0x01 << i );
		
		//上升沿把数据写入DS1302_IO，因为要求最小延时为纳秒，51机器周期为1微秒，无需延时
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	//从最低位到最高位分别获得数据
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = byte & (0x01 << i );
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	DS1302_CE = 0;
	
}




//*********************************************** **

//功能：DS1302读操作
//返回类型：unsigned char
//形参：unsigned char 命令

//*************************************************
unsigned char  DS1302_ReadByte(unsigned char cmd)
{
	unsigned char i;
	unsigned char temp = 0x00;
	
	DS1302_CE = 1;
	
	//从最低位到最高位分别获得命令
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = cmd & (0x01 << i );
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
		
	}
	
	//读操作
	for(i = 0; i < 8; i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		
		//如果此bit为1
		if(DS1302_IO)
		{
			temp |= 0x01 << i;
		}
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0;
	
	//BCD（16进制）转十进制
	return (temp/16*10 + temp%16);
}