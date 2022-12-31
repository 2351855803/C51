#ifndef __TIMER0_H__
#define __TIMER0_H__



void Timer0_Init();

//给定时器计数赋值
void Timer_Set(unsigned int num);

//开定时器
void Timer_Begain(unsigned char flag);

//计数
unsigned int Timer_Count();










#endif