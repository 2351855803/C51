#include "Delay.h"
#include "intrins.h"
#include <REGX52.H>
#include "LCD1602.h"
#include "AT24C02.h"
#include "SYN6288.h"
#include <stdio.h>
//���Ŷ���
sbit DHT11_DQ = P2^3;
sbit LED_RED = P2^2;


//DHT11�洢
static unsigned char arr[5];


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



/**
  *@brief	lcd��ʾ�¶�ʪ��
  *@param	void
  *@return	void
 */
void DHT11_LCD1602_Show()
{
	Lcd_write_string(0X80,"NowHum:");
	Lcd_write_string(0Xc0,"NowTmp:");
	//��ȡ���洢
	if(0 == DHT11_Read_5_Byte(arr))
	{
		Lcd_write_number(1,8,arr[0]);
		Lcd_write_number(2,8,arr[2]);
		Delayms(500);
	}
	
	
	
}


/**
  *@brief	�¶�ʪ�ȱ���
  *@param	���������ٽ�ֵ
  *@return	����ֵ��ΪPWM�ıȽ�ֵ�����Ƶ����ת���ٶ�
 */
unsigned char DHT11_H_Alarm(unsigned char * humHWarn,unsigned char * tmpHWarn)
{
	/* ʵ����Ҫ�����whileע�͵��������޷����� */
	//while(0 != DHT11_Read_5_Byte(arr));
	if(arr[0] > (*humHWarn) && arr[2] > (*tmpHWarn))
	{
		//P3_0 = 1;
		return 9;
	}else if
	((arr[0] > (*humHWarn)) || (arr[2] > (*tmpHWarn)))
	{
		//P3_0 = 1;
		return 2;
	}

	return 0;

	
}

/**
  *@brief	�¶�ʪ����ʪ�ȹ��ͱ���
  *@param	
  *@return	
 */
void DHT11_L_Alarm(unsigned char * humLWarn,unsigned char * tmpLWarn)
{
	//LED_RED = 1;
	/* ʵ����Ҫ�����whileע�͵��������޷����� */
	//while(0 != DHT11_Read_5_Byte(arr));
	if((arr[0] < (*humLWarn)) || (arr[2] < (*tmpLWarn)))
	{
		LED_RED = 0;
	}else if((arr[0] > (*humLWarn)) && (arr[2] > (*tmpLWarn)))
	{
		LED_RED = 1;
	}

	
}

/**
  *@brief	��ֹ�趨�������޳�����
  *@param	
  *@return	
 */
void DHT11_SetAlarn(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	//ʪ������
	if((*humHWarn) > 99) { (*humHWarn) = 99; }
	if((*humHWarn) <= 50) { (*humHWarn) = 50; }
	//ʪ������
	if((*humLWarn) < 15 ) { (*humLWarn) = 15;  }
	if((*humLWarn) > 50 ) { (*humLWarn) = 50;  }
	//�¶�����
	if((*tmpHWarn) > 40 ) { (*tmpHWarn) = 40;  }
	if((*tmpHWarn) <= 25 ) { (*tmpHWarn) = 25;  }
	//�¶�����
	if((*tmpLWarn) < 5  ) { (*tmpLWarn) = 5;   }
	if((*tmpLWarn) > 25  ) { (*tmpLWarn) = 25;   }
}




/**
  *@brief	��ȡat24c02�е����ݱ��浽������
  *@param	
  *@return	
 */
void DHT11_SaveDH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn)
{
	*humHWarn = AT24C02_Read(1);
	*humLWarn = AT24C02_Read(2);
	*tmpHWarn = AT24C02_Read(3);
	*tmpLWarn = AT24C02_Read(4);
	DHT11_SetAlarn(humHWarn,humLWarn,tmpHWarn,tmpLWarn);
}

void DHT11_SynRead()
{
	char DH[15] = 0;
	sprintf(DH,"%s%d","��ǰʪ��Ϊ",arr[0]);
	SYN_FrameInfo(0, DH);
	Delayms(10000);
}

