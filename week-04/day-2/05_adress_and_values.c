#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Print out the addresses with and without pointer
print out the values with and without pointer
 */


int main()
{
    int number = 2017;
    int *num_addr;
    num_addr = &number;
    float Pi = 3.14;
    float *pi_addr;
    pi_addr = &Pi;
    char letter = 't';
	char *let_addr;
    let_addr = &letter;
    printf("addresses: %x %x %x %x %x %x \n", num_addr, &number, pi_addr, &Pi, let_addr, &letter);
    printf("values: %d %d %.2f %.2f %c %c \n", *num_addr, number, *pi_addr, Pi, *let_addr, letter);
    return 0;
}
