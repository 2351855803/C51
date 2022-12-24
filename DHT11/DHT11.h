#ifndef __DHT11_H__
#define __DHT11_H__

void DHT11_Rst();
unsigned char DHT11_Check();
unsigned char DHT11_Receive();
unsigned char DHT11_Read_5Byte(unsigned char * tempH, unsigned char * tempL, unsigned char * humiH, unsigned char * humiL);




#endif



