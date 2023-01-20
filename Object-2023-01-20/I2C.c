#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;


/**
  *@brief  I2C��ʼ
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
  *@brief  I2C����
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
  *@brief  I2C��������
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
  *@brief  I2C������
  *@param   void 
  *@return  unsigned char 
 */
unsigned char I2C_ReadByte()
{
	unsigned char i;
	unsigned char temp = 0x00;
	//��������ǰ�ͷ�SDA
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
  *@brief  I2C����Ӧ��  0ΪӦ��1Ϊ��Ӧ��
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
  *@brief  I2C����Ӧ��  
  *@param   void
  *@return  unsigned char
 */

unsigned char I2C_ReceivedAck()
{
	unsigned char Ack;
	//��������ǰ�ͷ�SDA
	I2C_SDA = 1;
	Ack = I2C_SDA;
	I2C_SCL = 1;
	I2C_SCL = 0;
	return Ack;
}




