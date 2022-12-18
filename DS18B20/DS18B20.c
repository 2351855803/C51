#include <REGX52.H>
#include "OneWire.h"

/**
  *@brief  开始温度转换
  *@param   void
  *@return	返回接收的位
 */
void DS18B20_ConvertT()
{
	OneWire_Init();
	OneWire_SendByte(0xCC);
	OneWire_SendByte(0x44);
}

/**
  *@brief  接收温度
  *@param   void
  *@return	返回温度
 */
float DS18B20_ReadT()
{
	int LSB, MSB;
	int temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(0xCC);
	OneWire_SendByte(0xBE);
	LSB = OneWire_ReceiveByte();
	MSB = OneWire_ReceiveByte();
	temp = MSB * 256 + LSB;
	T = temp / 16.0;
	return T;
	
}
