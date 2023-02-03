#include "Delay.h"
#include "intrins.h"
#include <REGX52.H>
#include "LCD1602.h"
#include "AT24C02.h"
#include "SYN6288.h"
#include <stdio.h>
#include "Key.h"
//引脚定义
sbit DHT11_DQ = P2^3;
sbit LED_RED = P2^2;


//DHT11存储
static char arr[5];


/**
  *@brief	DHT11复位
  *@param
  *@return
 */
void DHT11_Rst()
{
	DHT11_DQ = 1;
	//主机至少拉低18ms
	DHT11_DQ = 0;
	Delay20ms();
	//主机拉高20-40us
	DHT11_DQ = 1;
	Delay30us();	
}

/**
  *@brief	DHT11判断响应
  *@param
  *@return	0响应 其他均为异常
 */
unsigned char DHT11_Check()
{
	unsigned char Ack = 0;
	unsigned char time = 0;
	
	//等待DQ被拉低
	time = 0;
	while(DHT11_DQ)
	{
		_nop_();
		time++;
		if(time > 100) {return 101;}
	}
	//已经被拉低，接受响应
	Ack = DHT11_DQ;
	//跳过DHT11_DQ低电平信号时间
	time = 0;
	while(!DHT11_DQ)
	{
		_nop_();
		time++;
		if(time > 50) {return 102;}
	}
	//跳过DHT11_DQ高电平信号时间
	time = 0;
	while(DHT11_DQ)
	{
		_nop_();
		time++;
		if(time > 50) {return 103;}
	}
	
	//运行到这里表示可以开始传输数据，返回0
	return Ack;
}

/**
  *@brief	DHT11接受一个字节
  *@param
  *@return	接受到的字节
 */
unsigned char DHT11_Read_1_Byte()
{
	unsigned char Byte = 0;
	unsigned char time = 0;
	unsigned char i = 0;
	
	for(i = 0; i < 8; i++)
	{
		//等待50us的低电平过去
		time = 0;
		while(!DHT11_DQ)
		{
			_nop_();
			time++;
			if(time > 50) {return 104;}
		}
		
		//低电平过去  延时40us    
		//26-28us表示0 70us表示1
		Delay40us();
		
		//读DQ状态
		if(DHT11_DQ) { Byte |= (0x80 >> i);}
		
		//等待高电平时间过去
		time = 0;
		while(DHT11_DQ)
		{
			_nop_();
			time++;
			if(time > 50) {return 105;}
		}
		
	}
	return Byte;
	
}


/**
  *@brief	DHT11读五个字节     湿度高八位  湿度低八位  温度高八位 温度低八位  校验位
  *@param
  *@return	判断故障
 */
unsigned char DHT11_Read_5_Byte(unsigned char * arr)
{
	unsigned char i = 0;
	DHT11_Rst();
	if(0 == DHT11_Check())
	{
		
		                      
//		for(i = 0; i < 5; i++)                              //    ????????????????????
//		{
//			*(arr+i) = DHT11_Read_1_Byte();
//			
//		}
		
		*(arr+0) = DHT11_Read_1_Byte();
		*(arr+1) = DHT11_Read_1_Byte();
		*(arr+2) = DHT11_Read_1_Byte();
		*(arr+3) = DHT11_Read_1_Byte();
		*(arr+4) = DHT11_Read_1_Byte();
		
		if(*(arr+0) + *(arr+1) + *(arr+2) + *(arr+3) == *(arr+4))
		{
			return 0;
		}
		else return 106;
	}
	else return 107;
	
}



/**
  *@brief	lcd显示温度湿度
  *@param	void
  *@return	void
 */
void DHT11_LCD1602_Show()
{
	Lcd_write_string(0X80,"NowHum:");
	Lcd_write_string(0Xc0,"NowTmp:");
	//读取并存储
	if(0 == DHT11_Read_5_Byte(arr))
	{
		Lcd_write_number(1,8,arr[0]);
		Lcd_write_number(2,8,arr[2]);
		Delayms(500);
	}
	
	
	
}


/**
  *@brief	温度湿度报警
  *@param	两个警报临界值
  *@return	返回值作为PWM的比较值来控制电机的转动速度
 */
unsigned char DHT11_H_Alarm(unsigned char * humHWarn,unsigned char * tmpHWarn)
{
	char flag = 0;
	/* 实物需要把这个while注释掉，否则无法测量 */
	//while(0 != DHT11_Read_5_Byte(arr));
	if(arr[0] > (*humHWarn) && arr[2] > (*tmpHWarn))
	{
		//P3_0 = 1;
		flag = 1;
	while(1 == flag)
	{
		
		
		if(0x77 == Matrix_key())
		{
			flag = 0;
		}
	}

		return 9;
	}else if
	((arr[0] > (*humHWarn)) || (arr[2] > (*tmpHWarn)))
	{
		//P3_0 = 1;
		return 2;
	}

	return 0;

	
}

/**
  *@brief	温度湿度温湿度过低报警
  *@param	
  *@return	
 */
void DHT11_L_Alarm(unsigned char * humLWarn,unsigned char * tmpLWarn)
{
	//LED_RED = 1;
	/* 实物需要把这个while注释掉，否则无法测量 */
	//while(0 != DHT11_Read_5_Byte(arr));
	if((arr[0] < (*humLWarn)) || (arr[2] < (*tmpLWarn)))
	{
		LED_RED = 0;
	}else if((arr[0] > (*humLWarn)) && (arr[2] > (*tmpLWarn)))
	{
		LED_RED = 1;
	}

	
}

/**
  *@brief	防止设定的上下限出问题
  *@param	
  *@return	
 */
void DHT11_SetAlarn(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	//湿度上限
	if((*humHWarn) > 99) { (*humHWarn) = 99; }
	if((*humHWarn) <= 50) { (*humHWarn) = 50; }
	//湿度下线
	if((*humLWarn) < 15 ) { (*humLWarn) = 15;  }
	if((*humLWarn) > 50 ) { (*humLWarn) = 50;  }
	//温度上限
	if((*tmpHWarn) > 40 ) { (*tmpHWarn) = 40;  }
	if((*tmpHWarn) <= 25 ) { (*tmpHWarn) = 25;  }
	//温度下线
	if((*tmpLWarn) < 5  ) { (*tmpLWarn) = 5;   }
	if((*tmpLWarn) > 25  ) { (*tmpLWarn) = 25;   }
}




/**
  *@brief	读取at24c02中的数据保存到变量中
  *@param	
  *@return	
 */
void DHT11_SaveDH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	*humHWarn = AT24C02_Read(1);
	*humLWarn = AT24C02_Read(2);
	*tmpHWarn = AT24C02_Read(3);
	*tmpLWarn = AT24C02_Read(4);
	DHT11_SetAlarn(humHWarn,humLWarn,tmpHWarn,tmpLWarn);
}

void DHT11_SynRead_H()
{
	char DH[20] = 0;
	int H = (int)arr[0];
	sprintf(DH,"%s%d","当前湿度",H);
	SYN_FrameInfo(0, DH);
	Delayms(8000);
	
}


void DHT11_SynRead_T()
{
	char DH[20] = 0;
	int T = (int)arr[2];
	sprintf(DH,"%s%d","当前温度",T);
	SYN_FrameInfo(0, DH);
	Delayms(8000);
}
