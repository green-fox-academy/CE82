#include <stdio.h>
int main() {
    char buffer[255];   // Buffer variable for user input
    char* x;

    //TODO:
    puts ("neved:");
    // Get the user's name with gets
	gets(buffer);
    //TODO:
    // Print it out with puts
	puts(buffer);
    //TODO:
    puts ("állatod neve: ");
    // Get the user's pet name with getch
	int i=-1;
  	do {
  		i++;
    	buffer[i]=getchar();    	
  	} while (buffer[i]!= '\n');
  	buffer[i+1]='\0';
    //TODO:
    // Print it out
	printf("%s",buffer); 
    return 0;
}
