#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init();
void DS1302_WriteByte(unsigned char cmd, byte);
unsigned char  DS1302_ReadByte(unsigned char cmd);


#endif