#include <stdio.h>
#include <math.h>

// This program should work correctly with the following input: 20, 400

int main()
{
	double number, result;
	printf("Please enter a number: ");
	fflush(stdin);
	scanf("%lf", &number);

	printf("Please enter the square of that number: ");
	fflush(stdin);
	scanf("%lf", &result);
	double tmp = pow(number,2);
	if (tmp) == result)
		printf(":)\n");
	else
		printf(":(\n");

	return 0;
}
