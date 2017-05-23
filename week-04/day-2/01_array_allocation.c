#include <stdio.h>
#include <stdlib.h>

int main() {
	int *pointer = NULL;
		
  // TODO:
  // Please allocate a 5 long array and fill it with numbers from 0 to 4, then print the whole array
  
	pointer = (int*) calloc(5, 5*sizeof(int));
	int i=0;
	
	for (i=0;i<5;i++) {
		*pointer=i;
		printf(" %d\n",*pointer);	
		pointer++;	
	}
	free(pointer);
  // Please delete the array before the program exits

  return 0;
}
