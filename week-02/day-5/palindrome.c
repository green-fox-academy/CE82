#include <stdio.h>
#include <string.h>

char* pali(char*s,int l){
	char c[l];
	for (int i=0;i<l;i++) c[i]=s[l-i-1];	
	return strcat(s,c);
}

int main() {
    char b1[255]; 
    puts ("szó:");  
	gets(b1);
	printf("-->%s\n",pali(b1,strlen(b1)));

    return 0;
}
