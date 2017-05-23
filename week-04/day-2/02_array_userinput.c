#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it shoud print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.
int main() 
{
	int num, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &num);

    ptr = (int*) malloc(num * sizeof(int));  //memory allocated using malloc
    printf("Enter elements of array: ");
    for(i = 0; i < num; ++i) {
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }
	
    printf("average = %.2f\n", (float)sum/num);
    free(ptr);
    return 0;
}
