#ifndef __LCD1602_H__
#define __LCD1602_H__

//Ğ´ÃüÁî
Write_cmd(unsigned char cmd);
//Ğ´Êı¾İ
Write_data(unsigned char cmd);
//LCD³õÊ¼»¯
Lcd_initial();
//Ğ´×Ö·û´®
void Lcd_write_string(char cmd, char* addr);
//Ğ´Êı×Ö
void Lcd_write_number(char line, char row , unsigned char number);


#endif