#include <REGX52.H>
#include "OneWire.h"


/**
  *@brief   开始温度转换
  *@param   void
  *@return	void
 */
 
void DS18B20_ReverseT()
{
	//OneWire_Init();
	if(!OneWire_Init())
	{
		OneWire_SendByte(0xCC);
		OneWire_SendByte(0x44);
	}

	
}


/**
  *@brief   读取温度
  *@param   void
  *@return	温度
 */
float DS18B20_ReadT()
{
	int LSB = 0;
	int MSB = 0;
	int temp = 0;
	float Temp = 0.0;
	//OneWire_Init();
	if(!OneWire_Init())
	{
		OneWire_SendByte(0xCC);
		OneWire_SendByte(0xBE);
		LSB = OneWire_ReceiveByte();
		MSB = OneWire_ReceiveByte();
		MSB = MSB << 8;
		temp = MSB | LSB;
		Temp = temp / 16.0;
		return Temp;
	}
	
	
	
	
}







