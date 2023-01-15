
#ifndef __DHT11_H__
#define __DHT11_H__






void DHT11_Rst();
unsigned char DHT11_Check();
unsigned char DHT11_Read_1_Byte();
unsigned char DHT11_Read_5_Byte(unsigned char * arr);
void DHT11_LCD1602_Show();
unsigned char DHT11_H_Alarm(unsigned char * humHWarn,unsigned char * tmpHWarn);







#endif