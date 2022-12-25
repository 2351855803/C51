#include "Delay.h"
#include "intrins.h"
#include <REGX52.H>



//引脚定义
sbit DHT11_DQ = P2^3;




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



