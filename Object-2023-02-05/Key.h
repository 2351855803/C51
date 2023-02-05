#ifndef __KEY_H__
#define __KEY_H__

unsigned char Key();
unsigned char Matrix_key();
void Matrix_Set_DH(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn);
void Key_OnetouchSet(unsigned char * humHWarn, unsigned char * humLWarn,\
			  unsigned char * tmpHWarn, unsigned char * tmpLWarn);


#endif