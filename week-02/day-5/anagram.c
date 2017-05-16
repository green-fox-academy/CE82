#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
int kisebbik(int a, int b){
	if (a>b)return b;
	else return a;
}
int compare (const void * a, const void * b){
	return ( *(char*)a - *(char*)b );
}


int main() {
    char b1[255];   
    char b2[255];
    
    
    puts ("Írj be két szót, hogy ellenőrizzem, anagrammák-e. \nElső szó:");  
	gets(b1);
	puts ("Második szó:");  
	gets(b2);
	qsort (b1, strlen(b1), sizeof(char), compare);
	qsort (b2, strlen(b2), sizeof(char), compare);
	
	if(strcmp (b1,b2))	printf("Ezek nem anagrammák\n"); //strcmp 0, ha egyforma
	else printf("Ezek  anagrammák\n");

    return 0;
}
