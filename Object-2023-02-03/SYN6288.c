#include <REGX52.H>
#include <string.h>


//串口1初始化
void UART1_Init(void)
{
	SCON = 0x50;		//8位数据,可变波特率
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES = 1;
	EA = 1;
}


void UART1_SendByte(unsigned char DAT)
{
	SBUF = DAT;
	while(TI == 0);
	TI=0;
}


void UART1_SendString(unsigned char *DAT, unsigned char len)
{
	unsigned char i;
	for(i = 0; i < len; i++)
	{
		UART1_SendByte(*DAT++);
	}
}




//Music:  0:无背景音乐  1~15:选择背景音乐
void SYN_FrameInfo(unsigned char Music, unsigned char *HZdata)
{
	
	unsigned char  Frame_Info[50];
	unsigned char  HZ_Length;
	unsigned char  ecc  = 0;  			//定义校验字节
	unsigned int i = 0;
	HZ_Length = strlen((char*)HZdata); 			//需要发送文本的长度


	Frame_Info[0] = 0xFD ; 			//构造帧头FD
	Frame_Info[1] = 0x00 ; 			//构造数据区长度的高字节
	Frame_Info[2] = HZ_Length + 3; 		//构造数据区长度的低字节
	Frame_Info[3] = 0x01 ; 			//构造命令字：合成播放命令
	Frame_Info[4] = 0x01 | Music << 4 ; //构造命令参数：背景音乐设定


	for(i = 0; i < 5; i++)   				//依次发送构造好的5个帧头字节
	{
		ecc = ecc ^ (Frame_Info[i]);		//对发送的字节进行异或校验
	}

	for(i = 0; i < HZ_Length; i++)   		//依次发送待合成的文本数据
	{
		ecc = ecc ^ (HZdata[i]); 				//对发送的字节进行异或校验
	}

	memcpy(&Frame_Info[5], HZdata, HZ_Length);
	Frame_Info[5 + HZ_Length] = ecc;
	UART1_SendString(Frame_Info, 5 + HZ_Length + 1);
}



