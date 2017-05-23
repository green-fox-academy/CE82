#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Add two numbers using pointers
*/


int main()
{

    int a  = 20;
    int b = 17;
	int *ptr1=&a;
	int *ptr2=&b;
	printf("%d\n", *ptr1+*ptr2);
    return 0;
}
