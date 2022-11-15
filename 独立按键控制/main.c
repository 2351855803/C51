#include<reg52.h>



//定义按键寄存器
sbit k1 = P3^1;
//定义LED
sbit led0 = P2^0;

//延时函数
void Delayms(unsigned int num)		//@12.000MHz
{
	unsigned char i, j;
	
		while(num--)
		{
			
				i = 2;
				j = 239;
				do
				{
					while (--j);
				} while (--i);
			

		}

	
}


int main()
{

	//-------------------------------------通过按钮来控制LED灯,长按亮，松手灭
//	P2 = 0Xff;
//	while(1)
//	{
//		
//		//k1为P3^1
//		if(0 == k1)
//		{
//			P2 = 0xfe;
//		}
//		else
//		{
//			P2 = 0xff;
//		}
//		
//	}
	

	//-------------------------------------按一下亮，按一下灭
//	while(1)
//	{
//			if(0 == k1)
//			{
//					//消除抖动，有两端，第二个delay表示消除抬起来的抖动
//					Delayms(20);
//					//表示一直按着按钮
//					while(0 == k1);
//					//抬起消抖
//					Delayms(20);
//					//取反
//					led0 = ~led0;

//			}

//		
//	}
	//-------------------------------------独立按键控制LED显示二进制
	//k1按下一下，加一
	
	 //临时储存用于P2取反
	int temp = 0x00;
	
	while(1)
	{
		if(0 == k1)
		{
			Delayms(20);
			while(0 == k1);
			Delayms(20);
			//消抖已经完成
			temp = temp + 1;
			P2 = ~a;
			
				
		}

	}
	
	
	return 0;
	
}
