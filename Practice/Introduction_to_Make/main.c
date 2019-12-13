#include "myHeader.h"
#include <stdio.h>

void main()
{
	int a = 5;
	int b = 0;
	int c = 10;

	printf("Factorial of %d: %d\n", a, factorial(a));
	printf("Factorial of %d: %d\n", b, factorial(b));
	printf("Factorial of %d: %d\n", c, factorial(c));
	printf("Sum of %d and %d: %d\n", a, c, add(a,c));
	printf("%d raised to %d: %d\n", a, b, power(a,b));
	printf("%d raised to %d: %d\n", b, a, power(b,a));
	printf("%d raised to %d: %d\n", c, a, power(c,a));
}

// compile entire module: gcc -O main.c factorial.c power.c add.c -o test
// run main using ./test

//Else, execute Makefile using 'make', which will execute the default statement.
//running 'make clean' will do 'rm test'