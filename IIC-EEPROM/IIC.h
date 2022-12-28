#ifndef __IIC_H__
#define __IIC_H__

void IIC_Start();
void IIC_Pause();
void IIC_SendByte(unsigned char Byte);
unsigned char IIC_ReadByte();
void IIC_SendAck(unsigned char Ack);
unsigned char IIC_ReceiveAck();












#endif