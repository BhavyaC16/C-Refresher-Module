#include "myHeader.h"

int power(int base, int exp)
{
	int p = 1;
	for(int i = 0; i<exp; i++)
	{
		p*=base;
	}
	return(p);
}