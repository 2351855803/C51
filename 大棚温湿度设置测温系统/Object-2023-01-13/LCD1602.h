#ifndef __LCD1602_H__
#define __LCD1602_H__

//д����
Write_cmd(unsigned char cmd);
//д����
Write_data(unsigned char cmd);
//LCD��ʼ��
Lcd_initial();
//д�ַ���
void Lcd_write_string(char cmd, char* addr);
//д����
void Lcd_write_number(char line, char row , unsigned char number);
//��ʼ����
void LCD_ShowBegin();
//�¶����ý���
void LCD_ShowSetTH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn);

#endif