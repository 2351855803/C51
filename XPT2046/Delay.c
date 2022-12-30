
void Delayms(unsigned char mm)		//@12.000MHz
{
	
	while(mm--)
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);		
	}
	
	
	

}
