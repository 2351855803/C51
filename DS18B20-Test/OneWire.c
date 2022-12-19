#include <REGX52.H>


sbit OneWire_DQ = P3^7;


/**
  *@brief   单总线初始化
  *@param   void
  *@return  响应 0  / 未响应 1
 */
unsigned char OneWire_Init()
{
	unsigned char i = 0;
	unsigned char Ack = 1;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 227; while (--i);  //@11.0592MHz 500us
	OneWire_DQ = 1;
	i = 17; while (--i);  //@11.0592MHz 40us
	Ack = OneWire_DQ;
	i = 227; while (--i);  //@11.0592MHz 500us
	return Ack;	
}
 

 
/**
  *@brief   单总线发送一个bit
  *@param   发送的数据
  *@return  void
 */ 

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	if(Bit)
	{
		i = 3; while (--i);  //@11.0592MHz 10us
		OneWire_DQ = 1;
	}
	else if(!Bit)
	{
		i = 40; while (--i);  //@11.0592MHz 90us
		OneWire_DQ = 1;	
	}
	i = 27; while (--i);  //@11.0592MHz 60us
	
}

/**
  *@brief   单总线接受一个bit
  *@param   void
  *@return  unsigned char 接收的bit
 */

unsigned char OneWire_ReceiveBit()
{
	unsigned char i = 0;
	unsigned char Bit = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 3; while (--i);  //@11.0592MHz 10us
	OneWire_DQ = 1;
	i = 4; while (--i);  //@11.0592MHz 12us
	Bit = OneWire_DQ;
	i = 27; while (--i);  //@11.0592MHz 60us
	return Bit;
}

/**
  *@brief   单总线发送一个byte
  *@param   发送的字节
  *@return  void
 */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		OneWire_SendBit(Byte & (0x01 << i) );
	}
	
}


/**
  *@brief   单总线接收一个byte
  *@param   void
  *@return  unsigned char 接收的byte
 */
unsigned char OneWire_ReceiveByte()
{
	unsigned char i = 0;
	unsigned char Byte = 0;
	for(i = 0; i < 8; i++)
	{
		if(OneWire_ReceiveBit()) {Byte |= (0x01 << i);}
	}
	
	return Byte;
}


