#include<stdio.h>

int main()
{
	char *x;
	printf("Default address to which x points: %p\n", x);
	printf("Default value of *x: %c\n", *x); 
	//*x = 'a';
	//printf("Address to which x points post assignment: %p\n", x);
	//printf("Value of x post assignment: %c\n", *x);

	char y = 'a';
	char *p = &y;
	printf("Value before incrementing pointer: %c\n", *p);
	p++;
	printf("Value after incrementing pointer: %c\n", *p);
}

// Default value of *x: 1
// Assignment *x = 'a' results in Segmentation fault

// Value before incrementing pointer: a
// Value after incrementing pointer: �