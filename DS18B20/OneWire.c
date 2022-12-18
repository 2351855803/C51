#include <REGX52.H>
#include "UART.h"
#include "Delay.h"


sbit OneWire_DQ = P3^7;


/**
  *@brief  单总线初始化
  *@param   void
  *@return	返回判断从机是否有响应主机 0响应 1没有响应
 */
unsigned char OneWire_Init()
{
	unsigned char i;
	unsigned char Ack = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	
	//至少延时480us
	i = 229; while (--i);  //@11.0592MHz 延时500us
	
	OneWire_DQ = 1;

	i = 29;  while (--i);	//@11.0592MHz 延时70us
	
	Ack = OneWire_DQ;		 
	
	i = 229; while (--i);  //@11.0592MHz 延时500us
	
	
	return Ack;
}


/**
  *@brief  发送一个bit
  *@param   发送的位
  *@return	void
 */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
//	i = 3;  while (--i);  //@11.0592MHz 延时10us
//	OneWire_DQ = Bit;
//	i = 22;  while (--i);  //@11.0592MHz 延时50us
	if(Bit)
	{
		i = 3;  while (--i);  //@11.0592MHz 延时10us
		OneWire_DQ = 1;
	}
	else
	{
		i = 29;  while (--i);	//@11.0592MHz 延时70us
		OneWire_DQ = 1;
	}
	

}

/**
  *@brief  接收位
  *@param   void
  *@return	返回接收的位
 */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i, Bit;
	OneWire_DQ = 0;
	i = 2;  while (--i);  //@11.0592MHz 延时5us
	i = 2;  while (--i);  //@11.0592MHz 延时5us
	OneWire_DQ = 1;
	Bit = OneWire_DQ;
	i = 22;  while (--i);  //@11.0592MHz 延时50us
	return Bit;
}

/**
  *@brief  发送字节
  *@param   发送的字节
  *@return	void
 */	
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		OneWire_SendBit(Byte & (0x01 << i));
	}	 
}

/**
  *@brief  接收字节
  *@param   void
  *@return	返回接收的字节
 */
unsigned char OneWire_ReceiveByte()
{
	unsigned char i;
	unsigned char Byte = 0;
	UART_Init();
	UART_Send(Byte);
	for(i = 0; i < 8; i++)
	{
		if(OneWire_ReceiveBit()) {Byte |= (0x01 << i);}
		
	}
	return Byte;
}