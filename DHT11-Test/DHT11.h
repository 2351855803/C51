
#ifndef __DHT11_H__
#define __DHT11_H__






void DHT11_Rst();
unsigned char DHT11_Check();
unsigned char DHT11_Read_1_Byte();
unsigned char DHT11_Read_5_Byte(unsigned char * arr);









#endif