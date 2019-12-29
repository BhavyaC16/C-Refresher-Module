#include<stdio.h>

int main()
{
	enum months {jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	enum months month;
	for(month = jan; month<=dec; ++month)
	{
		if(month==nov)
		{
			printf("%d NOVEMBER\n", month);
		}
		else if(month==2)
		{
			printf("February\n");
		}
		else
		{
			printf("month = %d\n", month);
		}
	}
	return(0);
}

//NOTE: ++month increments the enum by one even if the values are 
//      not contiguous.