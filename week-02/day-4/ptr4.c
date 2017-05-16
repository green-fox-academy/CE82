#include <stdio.h>

int main() {
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer;
    //TODO:
    // The "number_pointer" should point to the first element of the array called "numbers",
	number_pointer=&numbers;
    // than please print its value with it.
	for (int i=0; i<sizeof(numbers)/sizeof(int);i++){
		printf("%d ",*number_pointer);
		*number_pointer++;
	}
	printf("\n");
    return 0;
}
