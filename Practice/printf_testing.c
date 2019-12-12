#include <stdio.h>

int main()
{
	int i = 90;
	float f = 3;

	printf("f = %f \ni = %d\n",f);
	printf("f = %f \n", f, i);
	printf("i = %d \nf = %f\n", f, i);
}

/* WARNINGS UPON COMPILATION: */
// printf_testing.c:8:24: warning: format ‘%d’ expects a matching ‘int’ argument [-Wformat=]
//   printf("f = %f \ni = %d\n",f);
//                        ~^
// printf_testing.c:9:9: warning: too many arguments for format [-Wformat-extra-args]
//   printf("f = %f \n", f, i);
//          ^~~~~~~~~~~
// printf_testing.c:10:15: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘double’ [-Wformat=]
//   printf("i = %d \nf = %f\n", f, i);
//               ~^
//               %f
// printf_testing.c:10:24: warning: format ‘%f’ expects argument of type ‘double’, but argument 3 has type ‘int’ [-Wformat=]
//   printf("i = %d \nf = %f\n", f, i);
//                        ~^
//                        %d