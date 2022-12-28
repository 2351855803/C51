#include <REGX52.H>
#include "IIC.h"
#include "Delay.h"

//AT24C02地址宏定义
#define AT24C02_Addr_Write   0xA0
#define AT24C02_Addr_Read    0xA1


/**
  *@brief	AT24C02字节写
  *@param	存储数据的存储地址，存储的数据
  *@return	void
 */
void AT24C02_Write(unsigned char ByteAddr,Byte)
{
	
	IIC_Start();
	IIC_SendByte(AT24C02_Addr_Write);
	IIC_ReceiveAck();
	IIC_SendByte(ByteAddr);
	IIC_ReceiveAck();
	IIC_SendByte(Byte);
	IIC_ReceiveAck();
	IIC_Pause();
	
	//写最少需要延时5ms
	Delayms(5);

}


/**
  *@brief	AT24C02读字节
  *@param	void
  *@return	字节的地址 ，存储的数据的地址（0-255）
 */
unsigned char AT24C02_Read(unsigned char ByteAddr)
{
	unsigned char Byte = 0;
	
	IIC_Start();
	IIC_SendByte(AT24C02_Addr_Write);
	IIC_ReceiveAck();
	IIC_SendByte(ByteAddr);
	IIC_ReceiveAck();
	
	IIC_Start();
	IIC_SendByte(AT24C02_Addr_Read);
	IIC_ReceiveAck();
	Byte = IIC_ReadByte();
	IIC_SendAck(1);
	IIC_Pause();
	
	
	
	
	
	return Byte;
}




