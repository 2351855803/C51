#ifndef __LCD1602_H__
#define __LCD1602_H__

//写命令
Write_cmd(unsigned char cmd);
//写数据
Write_data(unsigned char cmd);
//LCD初始化
Lcd_initial();
//写字符串
void Lcd_write_string(char cmd, char* addr);
//写数字
void Lcd_write_number(char line, char row , unsigned char number);
//开始界面
void LCD_ShowBegin();
//温度设置界面
void LCD_ShowSetTH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn);


#endif