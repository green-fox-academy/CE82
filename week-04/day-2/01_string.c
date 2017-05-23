#include <stdio.h>

int main() {
    char my_name_array[] = "My Name";
    char c=' ';
	//TODO:
    // Print out the array character-by-character
    int i=0;
	while(c!='\0'){
		c=my_name_array[i];
		printf("%c",c);
		i++;
	}
	printf("\n");
    return 0;
}
