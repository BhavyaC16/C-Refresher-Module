#include<stdio.h>
#include<string.h>

extern int add(int a, int b);
extern void display_result(char * result, int len);
extern void display_statement();

void int_to_string(char result[], int number)
{
    int rem;
    int len = 0;
    int temp = number;
    while(temp!=0)
    {
        len++;
        temp = temp/10;
    }
    for (int i=(len-1); i>=0; i--)
    {
        rem = number % 10;
        number = number / 10;
        result[i] = rem+'0';
    }
    result[len] = '\0';
}

void main()
{
	int a, b;
	printf("Enter integer A: ");
	scanf("%d", &a);
	printf("Enter integer B: ");
	scanf("%d", &b);
	int res = add(a, b);
	char result_string[11];
	int_to_string(result_string, res);
	int len = strlen(result_string);
    display_statement();
	display_result(result_string, len);
}
