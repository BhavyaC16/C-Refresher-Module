#include<stdio.h>

int main()
{
	int a = 0;
	int b = 0;
	int *p;
	int **m; // Pointer to an integer pointer

	a = 10;
	p = &a;
	printf("Memory address of a: %p\n", p);
	printf("Value of a: %d\n", *p);
	*p = 20;
	printf("Updated value of a: %d\n", a);
	p = &b;
	printf("Memory address of b: %p\n", p);

	m = &p; // m now points to p
	printf("Memory address of p: %p\n", m);
	return(0);
}