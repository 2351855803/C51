#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;


/**
  *@brief  I2C开始
  *@param   void 
  *@return  void 
 */
 
void I2C_Start()
{
	I2C_SCL = 1;
	I2C_SDA = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}
 
/**
  *@brief  I2C结束
  *@param   void 
  *@return  void 
 */

void I2C_Pause()
{
	I2C_SCL = 0;
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/**
  *@brief  I2C发送数据
  *@param   unsigned char 
  *@return  void 
 */

void I2C_SendByte(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		I2C_SDA = byte & 0x80 >> i;
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}


/**
  *@brief  I2C读数据
  *@param   void 
  *@return  unsigned char 
 */
unsigned char I2C_ReadByte()
{
	unsigned char i;
	unsigned char temp = 0x00;
	//主机接受前释放SDA
	I2C_SDA = 1;
	for(i = 0; i < 8; i++)
	{
		if(I2C_SDA) {temp |= (0x80 >> i);}
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
	return temp;
}

/**
  *@brief  I2C发送应答  0为应答1为非应答
  *@param   unsigned char
  *@return  void 
 */
void I2C_SendAck(unsigned char Ack)
{
	I2C_SDA = Ack;
	I2C_SCL = 1;
	I2C_SCL = 0;
}


/**
  *@brief  I2C接受应答  
  *@param   void
  *@return  unsigned char
 */

unsigned char I2C_ReceivedAck()
{
	unsigned char Ack;
	//主机接受前释放SDA
	I2C_SDA = 1;
	Ack = I2C_SDA;
	I2C_SCL = 1;
	I2C_SCL = 0;
	return Ack;
}




