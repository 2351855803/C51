#include <REGX52.H>


//���Ŷ���
sbit IIC_SCL = P2^1;
sbit IIC_SDA = P2^0;



/**
  *@brief	IIC��ʼ
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
  *@brief	IICֹͣ
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
  *@brief	IIC����һ���ֽ�
  *@param	���͵��ֽ�
  *@return	void
 */
void IIC_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		
		//��Ҫ���͵����ݷŵ�IIC_SDA�ϣ���λ��ǰ
		IIC_SDA = Byte & (0x80 >> i);
		
//		if(Byte & (0x80 >> i))
//		{
//			IIC_SDA = 1;
//		}else if(!(Byte & (0x80 >> i)))
//		{
//			IIC_SDA = 0;
//		}
		
		//���ߴӻ������ȡ
		IIC_SCL = 1;
		IIC_SCL = 0;
	}
}


/**
  *@brief	IIC����һ���ֽ�
  *@param	void
  *@return	���յ��ֽ�
 */
unsigned char IIC_ReadByte()
{
	unsigned char Byte = 0;
	unsigned char i = 0;
	//�ͷ�SDA
	IIC_SDA = 1;
	
	for(i = 0; i < 8; i++)
	{
		if(IIC_SDA) {Byte |= (0x80 >> i);}
		//�������������ȡ
		IIC_SCL = 1;
		IIC_SCL = 0;
	}
	
	
	
	return Byte;
}


/**
  *@brief	IIC����Ӧ��
  *@param	�Ƿ�Ӧ��
  *@return	void
 */
void IIC_SendAck(unsigned char Ack)
{
	IIC_SDA = Ack;
	IIC_SCL = 1;
	IIC_SCL = 0;
}


/**
  *@brief	IIC����Ӧ��
  *@param	void
  *@return	�ӻ��Ƿ�Ӧ��   0��ʾӦ�� 1��ʾ��Ӧ��
 */
unsigned char IIC_ReceiveAck()
{
	unsigned char Ack;
	
	//�ͷ�
	IIC_SDA = 1;
	
	
	IIC_SCL = 1;
	Ack = IIC_SDA;
	IIC_SCL = 0;
	
	
	return Ack;
}



