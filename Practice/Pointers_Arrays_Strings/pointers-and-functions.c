#include<stdio.h>

void swap(int *, int *);

int main()
{
	int a = 10;
	int b = 20;
	printf("Values before swapping: a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("Values after swapping: a = %d, b = %d\n", a, b);
	return(0);
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//NOTE: A similar mechanism can be used if you want a function to return 
//      more than 1 value (returning multiple values)