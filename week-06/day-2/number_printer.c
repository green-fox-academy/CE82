#include <stdio.h>
#include <stdint.h>

void printf_numbers(double from, double to)
{	
	for (double i = from; i < to; i++)
		printf("%.0f , ", i);
}

int main()
{
	printf_numbers(2147483600, 2147484600);
	return 0;
}
