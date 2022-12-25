#include "Delay.h"
#include "intrins.h"
#include <REGX52.H>



//���Ŷ���
sbit DHT11_DQ = P2^3;




/**
  *@brief	DHT11��λ
  *@param
  *@return
 */
void DHT11_Rst()
{
	DHT11_DQ = 1;
	//������������18ms
	DHT11_DQ = 0;
	Delay20ms();
	//��������20-40us
	DHT11_DQ = 1;
	Delay30us();	
}

/**
  *@brief	DHT11�ж���Ӧ
  *@param
  *@return	0��Ӧ ������Ϊ�쳣
 */
unsigned char DHT11_Check()
{
	unsigned char Ack = 0;
	unsigned char time = 0;
	
	//�ȴ�DQ������
	time = 0;
	while(DHT11_DQ)
	{
		_nop_();
		time++;
		if(time > 100) {return 101;}
	}
	//�Ѿ������ͣ�������Ӧ
	Ack = DHT11_DQ;
	//����DHT11_DQ�͵�ƽ�ź�ʱ��
	time = 0;
	while(!DHT11_DQ)
	{
		_nop_();
		time++;
		if(time > 50) {return 102;}
	}
	//����DHT11_DQ�ߵ�ƽ�ź�ʱ��
	time = 0;
	while(DHT11_DQ)
	{
		_nop_();
		time++;
		if(time > 50) {return 103;}
	}
	
	//���е������ʾ���Կ�ʼ�������ݣ�����0
	return Ack;
}

/**
  *@brief	DHT11����һ���ֽ�
  *@param
  *@return	���ܵ����ֽ�
 */
unsigned char DHT11_Read_1_Byte()
{
	unsigned char Byte = 0;
	unsigned char time = 0;
	unsigned char i = 0;
	
	for(i = 0; i < 8; i++)
	{
		//�ȴ�50us�ĵ͵�ƽ��ȥ
		time = 0;
		while(!DHT11_DQ)
		{
			_nop_();
			time++;
			if(time > 50) {return 104;}
		}
		
		//�͵�ƽ��ȥ  ��ʱ40us    
		//26-28us��ʾ0 70us��ʾ1
		Delay40us();
		
		//��DQ״̬
		if(DHT11_DQ) { Byte |= (0x80 >> i);}
		
		//�ȴ��ߵ�ƽʱ���ȥ
		time = 0;
		while(DHT11_DQ)
		{
			_nop_();
			time++;
			if(time > 50) {return 105;}
		}
		
	}
	return Byte;
	
}


/**
  *@brief	DHT11������ֽ�     ʪ�ȸ߰�λ  ʪ�ȵͰ�λ  �¶ȸ߰�λ �¶ȵͰ�λ  У��λ
  *@param
  *@return	�жϹ���
 */
unsigned char DHT11_Read_5_Byte(unsigned char * arr)
{
	unsigned char i = 0;
	DHT11_Rst();
	if(0 == DHT11_Check())
	{
		
		                      
//		for(i = 0; i < 5; i++)                              //    ????????????????????
//		{
//			*(arr+i) = DHT11_Read_1_Byte();
//			
//		}
		
		*(arr+0) = DHT11_Read_1_Byte();
		*(arr+1) = DHT11_Read_1_Byte();
		*(arr+2) = DHT11_Read_1_Byte();
		*(arr+3) = DHT11_Read_1_Byte();
		*(arr+4) = DHT11_Read_1_Byte();
		
		if(*(arr+0) + *(arr+1) + *(arr+2) + *(arr+3) == *(arr+4))
		{
			return 0;
		}
		else return 106;
	}
	else return 107;
	
}



