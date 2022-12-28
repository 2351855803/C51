#include <REGX52.H>
#include "IIC.h"
#include "Delay.h"

//AT24C02��ַ�궨��
#define AT24C02_Addr_Write   0xA0
#define AT24C02_Addr_Read    0xA1


/**
  *@brief	AT24C02�ֽ�д
  *@param	�洢���ݵĴ洢��ַ���洢������
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
	
	//д������Ҫ��ʱ5ms
	Delayms(5);

}


/**
  *@brief	AT24C02���ֽ�
  *@param	void
  *@return	�ֽڵĵ�ַ ���洢�����ݵĵ�ַ��0-255��
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




