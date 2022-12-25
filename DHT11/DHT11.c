#include "Delay.h"
#include <REGX52.H>
#include "UART.h"
#include "intrins.h"

//引脚定义
sbit DHT11_DQ = P2^3;

/**
  *@brief	DHT11复位
  *@param	void
  *@return	void
 */
void DHT11_Rst()
{
	DHT11_DQ = 1;
	DHT11_DQ = 0;
	//至少拉低18ms
	Delay20ms();
	DHT11_DQ = 1;
	//拉高20-40us
	Delay30us();	
}





/**
  *@brief	DHT11检查是否有返回信号
  *@param	void
  *@return	0有 1没有
 */
unsigned char DHT11_Check()
{
	unsigned char time = 0;
	unsigned char Ack = 1;
	
	time = 0;
	while(DHT11_DQ)
	{
		time++;
		_nop_();
		if(time > 100) {return 101;}
	}
	
	//判断低电平80us
	time = 0;
	while(!DHT11_DQ)
	{
		Ack = DHT11_DQ;
		time++;
		_nop_();
		if(time > 100) {return 102;}
	}
	
	
	//判断高电平80us
	time = 0;
	while(DHT11_DQ)
	{
		time++;
		_nop_();
		if(time > 100) {return 103;}
	}
	
	//返回0表示有应答
	return Ack;
	
}


/**
  *@brief	DHT11接受一个字节
  *@param	void
  *@return	接收的字节
 */
unsigned char DHT11_Receive()
{
	unsigned char i = 0;
	unsigned char time = 0;
	unsigned char byte = 0;
	
	
	
	for(i = 0; i < 8; i++)
	{
		
		//延时50us,等待过去
		time = 0;
		while(!DHT11_DQ)
		{
			time++;
			_nop_();
			if(time > 100) {return 201;}
		}
		
		
		//延时40us读取
		Delay40us();
		
		if(DHT11_DQ == 1)
		{
			byte |= (0x80 >> i);
			//等待高电平时间过去
			time = 0;
			while(DHT11_DQ)
			{
				time++;
				_nop_();
				if(time > 100) {return 202;}
			}
		}
		
	}

	return byte;	
}




/**
  *@brief	DHT11接受五个字节          湿度高八位 湿度低八位 温度高八位 温度低八位 校验位
  *@param	void
  *@return	返回来检查正常或者故障
 */
unsigned char DHT11_Read_5Byte(unsigned char * tempH, unsigned char * tempL, unsigned char * humiH, unsigned char * humiL)
{
	unsigned char arr[5];
	
	DHT11_Rst();
	if(0 == DHT11_Check())
	{
		
		arr[0] = DHT11_Receive();	//湿度高八位
		arr[1] = DHT11_Receive();	//湿度低八位
		arr[2] = DHT11_Receive();	//温度高八位
		arr[3] = DHT11_Receive();	//温度低八位
		arr[4] = DHT11_Receive();	//校验
		Delay40us();
		//校验正确
		if((arr[0] + arr[1] + arr[2] + arr[3]) == arr[4])
		{
			* tempH = arr[2];
			* tempL = arr[3];
			* humiH = arr[0];
			* humiL = arr[1];
		
		
			
		}
			
	}
	else {return 302;}

	//正常
	return 0;
}











