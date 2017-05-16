#include <stdio.h>

int main() {
    int int_array[] = {1, 654, 987, 654, 31};
    float float_array[] = {1.2, 3.14, 1.41, 0.707, 1.73};
    int size=sizeof(int_array)/sizeof(int);
    for (int i=0; i<size; i++){
		printf("%d%c",int_array[i],' ');
	}
	printf("\n");
	size=sizeof(float_array)/sizeof(float);
    for (int i=0; i<size; i++){
		printf("%1.3f%c",float_array[i],' ');
	}
	printf("\n");
	//TODO:
    // Print out the content of the arrays

    return 0;
}
