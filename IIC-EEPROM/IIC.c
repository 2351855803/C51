#include <REGX52.H>


//引脚定义
sbit IIC_SCL = P2^1;
sbit IIC_SDA = P2^0;



/**
  *@brief	IIC开始
  *@param	void
  *@return	void
 */
void IIC_Start()
{	
	IIC_SDA = 1;
	IIC_SCL = 1;
	IIC_SDA = 0;
	IIC_SCL = 0;
}

/**
  *@brief	IIC停止
  *@param	void
  *@return	void
 */
void IIC_Pause()
{
	IIC_SCL = 0;
	IIC_SDA = 0;
	IIC_SCL = 1;
	IIC_SDA = 1;	
}


/**
  *@brief	IIC发送一个字节
  *@param	发送的字节
  *@return	void
 */
void IIC_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		
		//把要发送的数据放到IIC_SDA上，高位在前
		IIC_SDA = Byte & (0x80 >> i);
		
//		if(Byte & (0x80 >> i))
//		{
//			IIC_SDA = 1;
//		}else if(!(Byte & (0x80 >> i)))
//		{
//			IIC_SDA = 0;
//		}
		
		//拉高从机将会读取
		IIC_SCL = 1;
		IIC_SCL = 0;
	}
}


/**
  *@brief	IIC接受一个字节
  *@param	void
  *@return	接收的字节
 */
unsigned char IIC_ReadByte()
{
	unsigned char Byte = 0;
	unsigned char i = 0;
	//释放SDA
	IIC_SDA = 1;
	
	for(i = 0; i < 8; i++)
	{
		if(IIC_SDA) {Byte |= (0x80 >> i);}
		//拉高主机将会读取
		IIC_SCL = 1;
		IIC_SCL = 0;
	}
	
	
	
	return Byte;
}


/**
  *@brief	IIC发送应答
  *@param	是否应答
  *@return	void
 */
void IIC_SendAck(unsigned char Ack)
{
	IIC_SDA = Ack;
	IIC_SCL = 1;
	IIC_SCL = 0;
}


/**
  *@brief	IIC接受应答
  *@param	void
  *@return	从机是否应答   0表示应答 1表示非应答
 */
unsigned char IIC_ReceiveAck()
{
	unsigned char Ack;
	
	//释放
	IIC_SDA = 1;
	
	
	IIC_SCL = 1;
	Ack = IIC_SDA;
	IIC_SCL = 0;
	
	
	return Ack;
}



