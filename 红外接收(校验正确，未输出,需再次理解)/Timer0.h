#ifndef __TIMER0_H__
#define __TIMER0_H__



void Timer0_Init();

//����ʱ��������ֵ
void Timer_Set(unsigned int num);

//����ʱ��
void Timer_Begain(unsigned char flag);

//����
unsigned int Timer_Count();










#endif