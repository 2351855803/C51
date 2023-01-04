#include <REGX52.H>

//_nop_()���õ�����ͷ�ļ�����������һ���������ڣ�12MhzΪ1us��11.0592MhzԼΪ1.08us
#include <intrins.h>


unsigned char zhengZhuan[8]={0xf2,0xf6,0xf4,0xfc,0xf8,0xf9,0xf1,0xf3}; 

unsigned char fanZhuan[8]={0xf1,0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3}; 

//����A B C�ĳ�ҩ����������
//����ֱ�洢 A��ҩ���� A���� B��ҩ���� B����  C��ҩ���� C����  �Լ���ҩ���
char User[6] = 0;
//User������±�
//static��ʾ��̬���������ź���������ʹ�øñ�������
static unsigned char num = 0;

//����洢���������
//���������
unsigned char _code[5] = {1,2,3,4,5};
unsigned char my_code[5] = {0,0,0,0,0};
//���������������


//��0-5 �ֱ�Ϊ A��Сʱ���� B��Сʱ���� C��Сʱ����
char ABC_setTime[7] = 0;
//ABC_setTime������±�
unsigned char set_timeI = 0;

//����ʱ�ӱ���
char hour = 0;
char minute = 0;
char second = 0;
//���峬����Сʱ���ѱ���
char Awarn_TimeMinute = 25;
char Awarn_TimeHour = 25;
char Bwarn_TimeMinute = 25;
char Bwarn_TimeHour = 25;
char Cwarn_TimeMinute = 25;
char Cwarn_TimeHour = 25;

//��ʱ��0����
static unsigned int timer0_count = 0;


//����lcd1602�Ĵ���
#define Lcdout P0

//�����ж��¶���û�д���35
unsigned char tempFlag = 0;

//������
sbit BUZZER = P1^4;
//LCD1602��������
sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;

//��ҩ�ĵ�
sbit A_LED = P2^0;
sbit B_LED = P2^1;
sbit C_LED = P2^2;

//�� �ر�ҩ��
sbit Motor_open = P1^6;
sbit Motor_off = P1^7;

//DS18B20
sbit DSPORT=P1^5;

//������״̬����
unsigned char motor_Flag = 0;

void Motor();

//*********************************************************************************************************************************************

 /**
  *@brief		  ��ʱ�����Ӻ���
  *@param	
  *@return
 */
void Delayms(unsigned char mm)	//��Ҫ��ʱ����ms���������
{
	
	while(mm--)
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);		
	}		

}

void Delay1ms(unsigned int n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}

void delay5(unsigned char n)
{
	do{_nop_();
	  	_nop_();
		_nop_();
		n--;
	  }
	  while(n);
}
//*********************************************************************************************************************************************
 /**
  *@brief		  DS18B20
  *@param	
  *@return
 */
unsigned char Ds18b20Init()
{
	unsigned char i;
	DSPORT=0;
	delay5(120);
	DSPORT=1;
	i=0;
	while(DSPORT)
	{
		Delay1ms(1);
		i++;
		if(i>5)
		return 0;
	}
	return 1;
}
unsigned char Ds18b20WriteByte(unsigned char dat)
{
	unsigned int i,j;
	for (j=0;j<8;j++)
	{
		DSPORT=0;
		i++;
		DSPORT=dat&0x01;
		delay5(12);
		DSPORT=1;
		dat>>=1;
	}
	return dat;
}
unsigned char Ds18b20ReadByte()
{
	unsigned char byte,bi,i,j;
	for(j=8;j>0;j--)
	{
		DSPORT=0;
		i++;
		DSPORT=1;
		i++;
		i++;
		bi=DSPORT;
		byte=(byte>>1)|(bi<<7);
		delay5(9);
	}
	return byte;
}
void Ds18b20ReadTempCom()
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);
	Ds18b20WriteByte(0x44);
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);
	Ds18b20WriteByte(0xbe);
}

int Ds18b20ReadTemp()
{
	int temp=0;
	unsigned char tmh,tml;
	Ds18b20ReadTempCom();
	tml= Ds18b20ReadByte();
	tmh= Ds18b20ReadByte();
	temp=tmh;
	temp<<=8;
	temp|=tml;
	return temp;
}

//*********************************************************************************************************************************************
 /**
  *@brief		  ����ΪLCD1602�Ӻ���
  *@param	
  *@return
 */                                              


//��������  RS = 0
void Write_cmd(unsigned char cmd)
{

	RS = 0;
	RW = 0;
	EN = 0;

	//��Ƭ����Ҫ���͵����ݷŵ�����������
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);

	
}
void Write_data(unsigned char cmd)
{

	RS = 1;
	RW = 0;
	EN = 0;

	//��Ƭ����Ҫ���͵����ݷŵ�����������
	Lcdout = cmd;
	
	EN = 1;
	
	_nop_();

      EN = 0;
	
	Delayms(1);
	

}
void Lcd_initial()
{

	Write_cmd(0x01);
	Write_cmd(0x06);
	
	Write_cmd(0x0c);
	Write_cmd(0x38);
	

	
	Delayms(1);
	
	
}

void Lcd_write_string(char cmd, char* addr)
{
	while(*addr != '\0')
	{
		Write_cmd(cmd++);
		Write_data(*addr);
		addr++;
	}
}



//�ڵڼ��еڼ�����ʾ����
//�β��б��У��У����֣�

void Lcd_write_number(char line, char row ,unsigned int number)
{
	if(1 == line)
	{
		Write_cmd(0x80+row-1);
		Write_data((number/10)+0x30);
		Write_data((number%10)+0x30);
	}
	else if(2 == line)
	{
		Write_cmd(0xc0+row-1);
		Write_data((number/10)+0x30);
		Write_data((number%10)+0x30);
	}
}


//*********************************************************************************************************************************************
/**
  *@brief		������̺���
  *@param	
  *@return
 */
//��ⰴ��
unsigned char Matrix_key()
{
	unsigned char n = 0;
	unsigned char m = 0;
	P3=0xf0;
	
	//��⵽�а������£�����λ����һ�����0
	if((P3&0xf0)!=0xf0);
	{
		Delayms(10);
			
		if((P3&0xf0)!=0xf0);
		{
			//ȡ����λ
			n=P3&0xf0;
			
			P3=0x0f;

			//ȡ����λ
			m=P3&0x0f;
			
			return(n+m);
		}
	}
}	
//ͨ��������̰��·���ֵ
//unsigned char Matrix_keyReturn()
//{
//	unsigned char temp;
//	
//	switch(Matrix_key())
//	{
//		case 0xee: temp = 1; while(Matrix_key() == 0xee);break;
//		case 0xde: temp = 2; break;
//		case 0xbe: temp = 3; break;
//		case 0x7e: temp = 4; break;
//		case 0xed: temp = 5; break;
//		case 0xdd: temp = 6; break;
//		case 0xbd: temp = 7; break;
//		case 0x7d: temp = 8; break;
//		case 0xeb: temp = 9; break;
//		case 0xdb: temp = 0; break;
////		case 0xbb: temp =11; break;
////		case 0x7b: temp =12; break;
////		case 0xe7: temp =12; break;
////		case 0xd7: temp =12; break;
////		case 0xb7: temp =12; break;
////		case 0x77: temp =12; break;
//		
//		
//	}
//	
//	return temp;
//}
//���������±�
static unsigned char code_num = 0;
//������ȷ���뷵��1Ҫ��ȻΪ0
unsigned char Code()
{
	
	unsigned char temp = 0;
	

	switch(Matrix_key())
	{
		case 0xee: temp = 1;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xee);break;
		case 0xde: temp = 2;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xde);break;
		case 0xbe: temp = 3;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xbe);break;
		case 0x7e: temp = 4;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0x7e);break;
		case 0xed: temp = 5;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xed);break;
		case 0xdd: temp = 6;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xdd);break;
		case 0xbd: temp = 7;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xbd);break;
		case 0x7d: temp = 8;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0x7d);break;
		case 0xeb: temp = 9;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xeb);break;
		case 0xdb: temp = 0;  my_code[code_num] = temp;  code_num++; while(Matrix_key() == 0xdb);break;	
		
	}
	code_num %= 5;
	
	if(my_code[0] == _code[0] && my_code[1] == _code[1] &&  my_code[2] == _code[2] &&  my_code[3] == _code[3] &&  my_code[4] == _code[4] )
	{
		return 1;
	}
	
	
	return 0;
	
}
//*********************************************************************************************************************************************
/**
  *@brief		ABC����
  *@param	
  *@return
 */
//����ABC����
void ABC_Limit()
{
	User[0] %= 4;
	User[2] %= 4;
	User[4] %= 4;
	User[1] %= 10;
	User[3] %= 10;
	User[5] %= 10;
}
//����ABC����
void A_B_C_Set()
{
	
	if(0xe7 == Matrix_key())
	{
		User[num]++;
		while(0xe7 == Matrix_key());
	}else if(0xd7 == Matrix_key())
	{
		User[num]--;
		while(0xd7 == Matrix_key());
	}else if(0xb7 == Matrix_key())
	{
		num++;
		if(num > 5) {num = 0;}
		while(0xb7 == Matrix_key());
	}
	ABC_Limit();
	Write_cmd(0xc1);
	Write_data(':');
	Write_data(User[0]+0x30);
	Write_data(User[1]+0x30);
	Write_cmd(0xc5);
	Write_data(':');
	Write_data(User[2]+0x30);
	Write_data(User[3]+0x30);
	Write_cmd(0xc9);
	Write_data(':');
	Write_data(User[4]+0x30);
	Write_data(User[5]+0x30);
	Write_cmd(0xcd);
	Write_data((num+1)+0x30);
	

	
}

//����ABC��ҩʱ���Сʱ��������
void ABCTime_Judge()
{
	unsigned char i = 0;
	for(i = 0; i <=5; i+=2)
	{
		if(ABC_setTime[i] >= 24)
		{
			ABC_setTime[i] = 0;
		}else if(ABC_setTime[i] < 0)
		{
			ABC_setTime[i] = 23;
		}
	}
	
	for(i = 1; i <= 5; i+=2)
	{
		if(ABC_setTime[i] >= 60)
		{
			ABC_setTime[i] = 0;
		}else if(ABC_setTime[i] < 0)
		{
			ABC_setTime[i] = 59;
		}
	}
	
	
}

//����ABC��ҩʱ��
void ABC_SetEatTime()
{
	while(Matrix_key() != 0x77 || ABC_setTime[6] < 4)
	{
		//���ʱ���Ƿ�Ϸ�
		ABCTime_Judge();
		
		//�����ҩ���С��4h
		if(ABC_setTime[6] < 4)
		{
			Lcd_write_string(0x8d,"!");
		}else 
		{
			Lcd_write_string(0x8d," ");
	
		}
		//��ҩ���С��24
		ABC_setTime[6] %= 25;
		if(ABC_setTime[6] < 0) {ABC_setTime[6] = 23;}
		
		//����ABC��ҩʱ��
		Lcd_write_string(0x80,"Set:");
		Lcd_write_string(0xC0,"A");
		Lcd_write_number(2,2,ABC_setTime[0]);
		Lcd_write_string(0xC3,":");
		Lcd_write_number(2,5,ABC_setTime[1]);
			
		Lcd_write_string(0x87,"B");
		Lcd_write_number(1,9,ABC_setTime[2]);
		Lcd_write_string(0x8a,":");
		Lcd_write_number(1,12,ABC_setTime[3]);
			
		Lcd_write_string(0xc7,"C");
		Lcd_write_number(2,9,ABC_setTime[4]);
		Lcd_write_string(0xca,":");
		Lcd_write_number(2,12,ABC_setTime[5]);
		
		//���ü��
		Lcd_write_number(1,15,ABC_setTime[6]);	
		if(0xe7 == Matrix_key())
		{
			ABC_setTime[set_timeI]++;
			while(0xe7 == Matrix_key());
		}else if(0xd7 == Matrix_key())
		{
			ABC_setTime[set_timeI]--;
			while(0xd7 == Matrix_key());
		}else if(0xb7 == Matrix_key())
		{
			set_timeI++;
			if(set_timeI > 6) {set_timeI = 0;}
			while(0xb7 == Matrix_key());
		}	
		
		//��ʾ�±�
		Lcd_write_number(1,5,(set_timeI+1));
	}
	//����
	Write_cmd(0x01);
	//��ʱ��ֹ�Ѻ�����Ҫ��Ҳ������
	Delayms(10);
	
}

unsigned char tempA = 0;
unsigned char tempB = 0;
unsigned char tempC = 0;


//��ʱ���ABC�ĵ�����������
unsigned char ABC_Warn()
{
	
	if(hour == ABC_setTime[0] && minute == ABC_setTime[1] && User[0] != 0)
	{
		//��Aҩ
		Awarn_TimeMinute = ABC_setTime[1] + 30;
		Awarn_TimeHour = ABC_setTime[0];
		if(Awarn_TimeMinute >= 60)
		{
			Awarn_TimeMinute = Awarn_TimeMinute - 60;
			Awarn_TimeHour = ABC_setTime[0] + 1;
			
		}
		tempA = 1;

		return 1;
	}else if(hour == ABC_setTime[2] && minute == ABC_setTime[3] && User[2] != 0)
	{
		//��Bҩ
		Bwarn_TimeMinute = ABC_setTime[3] + 30;
		Bwarn_TimeHour = ABC_setTime[2];
		if(Bwarn_TimeMinute >= 60)
		{
			Bwarn_TimeMinute = Bwarn_TimeMinute - 60;
			Bwarn_TimeHour = ABC_setTime[2] + 1;
		}

		tempB = 1;
		return 2;
		
	}else if(hour == ABC_setTime[4] && minute == ABC_setTime[5] && User[4] != 0)
	{
		//��Cҩ
		Cwarn_TimeMinute = ABC_setTime[5] + 30;
		Cwarn_TimeHour = ABC_setTime[4];
		if(Cwarn_TimeMinute >= 60)
		{
			Cwarn_TimeMinute = Cwarn_TimeMinute - 60;
			Cwarn_TimeHour = ABC_setTime[4] + 1;
		}
		tempC = 1;
		return 3;
		
	}
	return 0;
}


//�ж��Ƿ��ҩ��
void ABCEat_Judge()
{
	//A��ʱ����û��ҩ
	if(tempA == 1 && !motor_Flag && User[0] != 0)
	{
		A_LED = 0; B_LED = 1; C_LED = 1;
		Lcd_write_string(0x89,"A");
		
	}else if(tempA == 1 && motor_Flag )
	{//����Aҩ
		
		A_LED = 1; B_LED = 1; C_LED = 1;
		Lcd_write_string(0x89,"A!");
		Delayms(4000);
		Lcd_write_string(0x89,"  ");
		
		User[0]--;
		if(User[0] < 0 ) {User[0] = 0;}
		//�򿪺��־����
		motor_Flag = 0;
		ABC_setTime[0] += ABC_setTime[6];
		Awarn_TimeMinute = 25;
		Awarn_TimeHour = 25;
		
		tempA = 0;
	}
	
	
	
		//B��ʱ����û��ҩ
	if(tempB == 1 && !motor_Flag && User[2] != 0)
	{
		A_LED = 1; B_LED = 0; C_LED = 1;
		Lcd_write_string(0x89,"B");
		
	}else if(tempB == 1 && motor_Flag )
	{//����Bҩ
		
		A_LED = 1; B_LED = 1; C_LED = 1;
		Lcd_write_string(0x89,"B!");
		Delayms(4000);
		Lcd_write_string(0x89,"  ");
		
		User[2]--;
		if(User[2] < 0 ) {User[2] = 0;}
		//�򿪺��־����
		motor_Flag = 0;
		ABC_setTime[2] += ABC_setTime[6];
		Bwarn_TimeMinute = 25;
		Bwarn_TimeHour = 25;
		
		tempB = 0;
	}
	
	
	
	
	
	
	//C��ʱ����û��ҩ
	if(tempC == 1 && !motor_Flag && User[4] != 0)
	{
		A_LED = 1; B_LED = 1; C_LED = 0;
		Lcd_write_string(0x89,"C");
		
	}else if(tempC == 1 && motor_Flag )
	{//����Cҩ
		
		A_LED = 1; B_LED = 1; C_LED = 1;
		
		Lcd_write_string(0x89,"C!");
		Delayms(4000);
		Lcd_write_string(0x89,"  ");
		
		User[4]--;
		if(User[4] < 0 ) {User[0] = 0;}
		//�򿪺��־����
		motor_Flag = 0;
		ABC_setTime[4] += ABC_setTime[6];
		Cwarn_TimeMinute = 25;
		Cwarn_TimeHour = 25;
		tempC = 0;
	}

	
	
	
}
//*********************************************************************************************************************************************

/**
  *@brief		��ʱ��0��ʼ��
  *@param	
  *@return
 */
void Timer0_Init()
{
	//�򿪶�ʱ��0��1ģʽ
	TMOD &= 0xf0;
	TMOD |= 0x01;
	
	//����TCON
	TF0 = 0;
	TR0 = 1;
	
	//���ü�ʱʱ��
	//��������10000 == 10000us == 10ms == 0.01s
	//TH0��TL0Ϊ��λ���ֱ��һ��ʮ��λ�ĸ߰�λ�Ͱ�λ��ֵ
	TH0 = (65535 - 10000)/256;
	TL0 = (65535 - 10000)%256;
	
	//���ж�
	ET0 = 1;
	//���ж�
	EA = 1;
}

//ʱ���жϺ���
void Time_Judge()
{
	if(second >= 60)
	{
		minute++;
		second = 0;
	}else if(minute >= 60)
	{
		hour++;
		minute = 0;
	}else if(hour >= 24)
	{
		hour = 0;
	}else if(minute < 0)
	{
		minute = 59;
		hour--;
	}else if(hour < 0)
	{
		hour = 23;
	}
}

//ʱ����ʾ����
void Time_Show()
{
	Time_Judge();
	Lcd_write_string(0X82,":");
	Lcd_write_number(1,1,hour);
	Lcd_write_number(1,4,minute);

}

//����ʱ��
void Time_Set()
{
	//�ּ�
	if(0xbb == Matrix_key())
	{
		Delayms(10);
		if(0xbb == Matrix_key())
		{
			minute += 5;
			while(0xbb == Matrix_key());
		}
	}
	//�ּ�
	if(0x7b == Matrix_key())
	{
		Delayms(10);
		if(0x7b == Matrix_key())
		{
			minute --;
			while(0x7b == Matrix_key());
		}
	}
}

//*********************************************************************************************************************************************
/**
  *@brief		 ������̺���
  *@param	
  *@return
 */

void Motor()
{
	unsigned char i = 0;
	unsigned char j = 0;
	if(0 == Motor_open && 0 == tempFlag)
	{
		Delayms(10);
		if(0 == Motor_open)
		{
			for(i = 0; i < 8; i++)
			{
				P1 = zhengZhuan[i];
				Delayms(100);
					
			}
		}
		

	}else if(0 == Motor_off && 0 == tempFlag)
	{
		Delayms(10);
		if(0 == Motor_off)
		{
			for(i = 0; i < 8; i++)
			{
				P1 = fanZhuan[i];
				Delayms(100);
					
			}
		}
		motor_Flag = 1;
	}
}


//*********************************************************************************************************************************************
//*********************************************************************************************************************************************
//*********************************************************************************************************************************************

void main()
{

	//�����¶�
	unsigned int tmp;
	//LCD1602��ʼ��
	Lcd_initial();
	//��ʱ��0��ʼ��
	Timer0_Init();

	//��ʾѧ�ź���λ
	Lcd_write_string(0xce,"47");
	
	
	//һ��ȥϵͳ����ABC�ĳ�ҩʱ�䣬������󣬳�ҩ��ʱ���洢��������
	ABC_SetEatTime();
	

	//һ��ȥϵͳ������ʱ����������
	while(Matrix_key() != 0xee)
	{
		//����ABC����
		Lcd_write_string(0xc0,"A");
		Lcd_write_string(0xc4,"B");
		Lcd_write_string(0xc8,"C");
		A_B_C_Set();
		
	}
	Write_cmd(0x01);
	//��ʱ��ֹ�Ѻ�����Ҫ��Ҳ������
	Delayms(10);
	
	
	
	while(1)
	{
		
		
		//��ҩʱ�䳬����Сʱ
		while ((minute == Awarn_TimeMinute && hour == Awarn_TimeHour && !motor_Flag)
			|| (minute == Bwarn_TimeMinute && hour == Bwarn_TimeHour && !motor_Flag)
			|| (minute == Cwarn_TimeMinute && hour == Cwarn_TimeHour && !motor_Flag))
		{
				
			//��ʾ����
			Write_cmd(0x8a);
			Write_data(my_code[0]+0x30);
			Write_data(my_code[1]+0x30);
			Write_data(my_code[2]+0x30);
			Write_data(my_code[3]+0x30);
			Write_data(my_code[4]+0x30);
			ABC_Warn();
			Motor();
			ABCEat_Judge();
			Code();
			if(motor_Flag == 1 && Code()){ break;}
			
		}
		Lcd_write_string(0x8a,"     ");
		
		
		//һ����������ó�ҩʱ���ABC����
		if(hour > 23)
		{
			//����
			Write_cmd(0x01);
			//��ʱ��ֹ�Ѻ�����Ҫ��Ҳ������
			Delayms(10);
			//���������ó�ҩ��ʱ��
			ABC_SetEatTime();
			
			//����������ABC����
			while(Matrix_key() != 0xee)
			{
				//����ABC����
				Lcd_write_string(0xc0,"A");
				Lcd_write_string(0xc4,"B");
				Lcd_write_string(0xc8,"C");
				A_B_C_Set();
				
			}
			Write_cmd(0x01);
			//��ʱ��ֹ�Ѻ�����Ҫ��Ҳ������
			Delayms(10);
			
		}
		
		
		//��ʾABCʣ��ĳ�ҩ����
		Lcd_write_string(0xc0,"A:");
		Write_cmd(0xc2); Write_data(User[0] + 0x30);
		
		Lcd_write_string(0xc4,"B:");
		Write_cmd(0xc6); Write_data(User[2] + 0x30);
		
		Lcd_write_string(0xc8,"C:");
		Write_cmd(0xca); Write_data(User[4] + 0x30);
		
		//��ʾѧ�ź���λ
		Lcd_write_string(0xce,"47");
		//�����¶�
		//Ϊʲô/16 ����Ϊds18b20��ʮ��λ��ɣ�Ȼ�����λ�������С��������ʵ���¶ȱȷ���ֵС2���Ĵη�������Ҫ��16
		tmp = (Ds18b20ReadTemp()/16);
		
		//�ж�������û�д���35
		if(tmp > 35) {tempFlag = 1;}
		else {tempFlag = 0;}
		if(tempFlag) {Lcd_write_string(0xcc,"!");}
		else {Lcd_write_string(0xcc," ");}
		
		//�������
		Motor();
//		Motor_Judge_ABC();
		
		//LCD��ʾ�¶�
		Lcd_write_string(0x86,"T");
		Lcd_write_number(1,8,tmp);

		//ʱ����ʾ ���� ABC����
		Time_Show();
		Time_Set();
		
		//�����趨�ĳ�ҩʱ��
		ABC_Warn();
		ABCEat_Judge();

	}
	
	
	
	
}


//���嶨ʱ��0�ж�
void Timer0_Routine() interrupt 1
{
	timer0_count++;
//	timer0_count == 100��ʾ��ȥ1s
	if( 100 == timer0_count)
	{
		second++;
		timer0_count = 0;
	}
	//��λ
	TH0 = (65535 - 10000)/256;
	TL0 = (65535 - 10000)%256;
}