#ifndef __SYN6288_H__
#define __SYN6288_H__

void SYN_FrameInfo(unsigned char Music, unsigned char *HZdata);
void UART1_SendString(unsigned char *DAT, unsigned char len);
void UART1_SendByte(unsigned char DAT);
void UART1_Init(void);








#endif