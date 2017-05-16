#include <stdio.h>
#include <stdlib.h>

#define TOTORO 19

// Define the TOTORO macro which holds the number of students in our class

int main()
{
    // Use the #ifdef and #ifndef macros!
    // If the TOTORO macro is not defined print out 32
    // If the TOTORO macro is defined print out it's value
    #ifdef TOTORO
    	printf("%d\n",TOTORO);
	#endif
	#ifndef TOTORO
    	printf("%d\n",32);
	#endif

    return 0;
}
