#include <stdio.h>

int main() {
    char buffer[255];   // Buffer variable for user input
    printf("írj valamit ide, aztán nyomj entert \n");
	scanf("%s",buffer);
    //TODO:
    // Get the user's name with scanf
	printf("ezt írtad: %s\n",buffer);
    //TODO:
    // Print it out with printf

    return 0;
}
