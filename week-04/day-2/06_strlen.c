#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function which receives a string as parameter, and returns
// the numbers of characters in the string.
// Don't use the strlen() function!
int len(char *str)
{
	char *c;
	c = str;
	int l = 0;
	while (*c != '\0') {
		c++;
		l++;
	}
	
	return l;
}

int main()
{
	printf("%d\n", len("jgds"));
    return 0;
}

