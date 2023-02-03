#ifndef __I2C_H__
#define __I2C_H__




void I2C_Start();
void I2C_Pause();
void I2C_SendByte(unsigned char byte);
unsigned char I2C_ReadByte();
void I2C_SendAck(unsigned char Ack);
unsigned char I2C_ReceivedAck();







#endif