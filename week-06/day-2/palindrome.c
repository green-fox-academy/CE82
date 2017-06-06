#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  palindrome(char *input);

int main()
{
	char input[100];
	printf("please enter a word: \n");
	scanf("%s", &input);
	palindrome(input);
	return 0;
}

void  palindrome(char *input)
{
	printf("%s", input);
	char *pointer;
	
	int i;
	for (i = 1; i < strlen(input); i++) {
		pointer = input + strlen(input) - (i+1);
		printf("%c", *pointer);
	}
	printf("\n");
}
