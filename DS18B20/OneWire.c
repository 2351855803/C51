#include <REGX52.H>
#include "UART.h"
#include "Delay.h"


sbit OneWire_DQ = P3^7;


/**
  *@brief  �����߳�ʼ��
  *@param   void
  *@return	�����жϴӻ��Ƿ�����Ӧ���� 0��Ӧ 1û����Ӧ
 */
unsigned char OneWire_Init()
{
	unsigned char i;
	unsigned char Ack = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	
	//������ʱ480us
	i = 229; while (--i);  //@11.0592MHz ��ʱ500us
	
	OneWire_DQ = 1;

	i = 29;  while (--i);	//@11.0592MHz ��ʱ70us
	
	Ack = OneWire_DQ;		 
	
	i = 229; while (--i);  //@11.0592MHz ��ʱ500us
	
	
	return Ack;
}


/**
  *@brief  ����һ��bit
  *@param   ���͵�λ
  *@return	void
 */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
//	i = 3;  while (--i);  //@11.0592MHz ��ʱ10us
//	OneWire_DQ = Bit;
//	i = 22;  while (--i);  //@11.0592MHz ��ʱ50us
	if(Bit)
	{
		i = 3;  while (--i);  //@11.0592MHz ��ʱ10us
		OneWire_DQ = 1;
	}
	else
	{
		i = 29;  while (--i);	//@11.0592MHz ��ʱ70us
		OneWire_DQ = 1;
	}
	

}

/**
  *@brief  ����λ
  *@param   void
  *@return	���ؽ��յ�λ
 */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i, Bit;
	OneWire_DQ = 0;
	i = 2;  while (--i);  //@11.0592MHz ��ʱ5us
	i = 2;  while (--i);  //@11.0592MHz ��ʱ5us
	OneWire_DQ = 1;
	Bit = OneWire_DQ;
	i = 22;  while (--i);  //@11.0592MHz ��ʱ50us
	return Bit;
}

/**
  *@brief  �����ֽ�
  *@param   ���͵��ֽ�
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
  *@brief  �����ֽ�
  *@param   void
  *@return	���ؽ��յ��ֽ�
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