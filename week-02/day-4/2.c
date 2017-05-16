#include <stdio.h>

int main() {
    
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";
    int i=0;
	while(char_array_the_same[i]!='\0'){
		printf("%c",char_array_the_same[i]);
		i++;
	}
	printf("\n");
	for (int i=0; i<sizeof(char_array); i++){
		printf("%c",char_array[i]);
	}
	
	printf("\n");
    return 0;
	//TODO:
    // Print out the two arrays character-by-character

	//TODO:
    // What is the difference between the arrays?
    //char_array nem nulla végű

    return 0;
}
