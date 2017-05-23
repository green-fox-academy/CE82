#include <stdio.h>
#include <stdlib.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/
char *conc(char *dest, const char *source)
{
	char *c;
	c = dest;
	while (*c!='\0') {
		c++;
	}
	//most c dest utolsó karakterére mutat, ahova írni lehet
	char *c2;
	c2 = source;
	while (*c2!='\0') {
		*c = *c2;
		c++;
		c2++;
	}
	*c2 = '\0';
	return dest;
}

int main()
{
	char str1[20] = "bab";
	char str2[] = "uci";
	printf("%s\n", conc(str1, str2));

    return 0;
}
