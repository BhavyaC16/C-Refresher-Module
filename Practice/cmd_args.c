#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("Number of arguments provided: %d\n", argc);
	
	int n, m;
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	printf("Argument 1: %d\nArgument 2: %d\n", n, m);
	return(0);
}

/* THINGS TO TRY:

./cmd_args 100 abc ==> Shows 0 for Argument 2
./cmd_args 100 ==> Segmentation fault (core dumped)
./cmd_args 100 12.5 ==> Shows 12 for Argument 2
*/