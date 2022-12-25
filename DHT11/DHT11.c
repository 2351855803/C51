#include "Delay.h"
#include <REGX52.H>
#include "UART.h"
#include "intrins.h"

//���Ŷ���
sbit DHT11_DQ = P2^3;

/**
  *@brief	DHT11��λ
  *@param	void
  *@return	void
 */
void DHT11_Rst()
{
	DHT11_DQ = 1;
	DHT11_DQ = 0;
	//��������18ms
	Delay20ms();
	DHT11_DQ = 1;
	//����20-40us
	Delay30us();	
}





/**
  *@brief	DHT11����Ƿ��з����ź�
  *@param	void
  *@return	0�� 1û��
 */
unsigned char DHT11_Check()
{
	unsigned char time = 0;
	unsigned char Ack = 1;
	
	time = 0;
	while(DHT11_DQ)
	{
		time++;
		_nop_();
		if(time > 100) {return 101;}
	}
	
	//�жϵ͵�ƽ80us
	time = 0;
	while(!DHT11_DQ)
	{
		Ack = DHT11_DQ;
		time++;
		_nop_();
		if(time > 100) {return 102;}
	}
	
	
	//�жϸߵ�ƽ80us
	time = 0;
	while(DHT11_DQ)
	{
		time++;
		_nop_();
		if(time > 100) {return 103;}
	}
	
	//����0��ʾ��Ӧ��
	return Ack;
	
}


/**
  *@brief	DHT11����һ���ֽ�
  *@param	void
  *@return	���յ��ֽ�
 */
unsigned char DHT11_Receive()
{
	unsigned char i = 0;
	unsigned char time = 0;
	unsigned char byte = 0;
	
	
	
	for(i = 0; i < 8; i++)
	{
		
		//��ʱ50us,�ȴ���ȥ
		time = 0;
		while(!DHT11_DQ)
		{
			time++;
			_nop_();
			if(time > 100) {return 201;}
		}
		
		
		//��ʱ40us��ȡ
		Delay40us();
		
		if(DHT11_DQ == 1)
		{
			byte |= (0x80 >> i);
			//�ȴ��ߵ�ƽʱ���ȥ
			time = 0;
			while(DHT11_DQ)
			{
				time++;
				_nop_();
				if(time > 100) {return 202;}
			}
		}
		
	}

	return byte;	
}




/**
  *@brief	DHT11��������ֽ�          ʪ�ȸ߰�λ ʪ�ȵͰ�λ �¶ȸ߰�λ �¶ȵͰ�λ У��λ
  *@param	void
  *@return	����������������߹���
 */
unsigned char DHT11_Read_5Byte(unsigned char * tempH, unsigned char * tempL, unsigned char * humiH, unsigned char * humiL)
{
	unsigned char arr[5];
	
	DHT11_Rst();
	if(0 == DHT11_Check())
	{
		
		arr[0] = DHT11_Receive();	//ʪ�ȸ߰�λ
		arr[1] = DHT11_Receive();	//ʪ�ȵͰ�λ
		arr[2] = DHT11_Receive();	//�¶ȸ߰�λ
		arr[3] = DHT11_Receive();	//�¶ȵͰ�λ
		arr[4] = DHT11_Receive();	//У��
		Delay40us();
		//У����ȷ
		if((arr[0] + arr[1] + arr[2] + arr[3]) == arr[4])
		{
			* tempH = arr[2];
			* tempL = arr[3];
			* humiH = arr[0];
			* humiL = arr[1];
		
		
			
		}
			
	}
	else {return 302;}

	//����
	return 0;
}











