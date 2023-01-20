#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRES  0xA0

/**
  *@brief   AT24C02Ð´
  *@param   unsigned char ´æ´¢µØÖ·£¨0-255£© ´æ´¢µÄÊý×Ö
  *@return  void
 */
void AT24C02_Write(unsigned char ByteAddr, Byte)
{
	
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRES);
	I2C_ReceivedAck();
	I2C_SendByte(ByteAddr);
	I2C_ReceivedAck();
	I2C_SendByte(Byte);
	I2C_ReceivedAck();
	I2C_Pause();
	
}

/**
  *@brief   AT24C02¶Á
  *@param   unsigned char ´æ´¢µÄµØÖ·
  *@return  unsigned char
 */

unsigned char AT24C02_Read(unsigned char ByteAddr)
{
	unsigned char temp;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRES);
	I2C_ReceivedAck();
	I2C_SendByte(ByteAddr);
	I2C_ReceivedAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRES | 0x01);
	I2C_ReceivedAck();
	temp = I2C_ReadByte();
	I2C_SendAck(1);
	I2C_Pause();
	
	return temp;
}


