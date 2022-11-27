#ifndef __MATRIXSCREEN_H__
#define __MATRIXSCREEN_H__


void _74HC595_Write(unsigned char byte);
void _74HC595_Initial();
void MatrixScreen_Show(unsigned char row, byte);

#endif