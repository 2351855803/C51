#include <REGX52.H>
#include <intrins.h>


//定义断码数组
char arr[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

//延时500ms
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




void temp(int num , int num1)
{
	//通过运算转换二进制给片选
	P2_2 = num%2;
	num /= 2;
	P2_3 = num%2;
	num /= 2;
	P2_4 = num%2;

	P0 = arr[num1];	
	
}


int main()
{
	//------------------------------------------  循环显示
	//临时测试函数,形参列表（第几个数码管亮，亮的数字）
	//数码管范围 0-7
	//可以隔着0.5s显示
//	while(1)
//	{
//		int i;
//		for(i = 0; i <= 7; i++)
//		{
//			Delay500ms();
//			temp(i,7);
//			
//		}		
//	}
	
	
	//------------------------------------------  动态显示0-9，间隔0.5s
	
	while(1)
	{
		int i;
		for(i = 0; i <= 7; i++)
		{
			Delay500ms();
			temp(i,i);
			
		}		
	}
	
	return 0;
}




