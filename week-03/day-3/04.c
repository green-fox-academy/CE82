#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */
int* resize(int* arr, int size, int newsize){
	int*uj=(int*)realloc(arr, newsize*sizeof(int));
	int*cntr=uj;
	//ez csak kiir
	printf("eredeti növelve: \n");
	for (int i=0; i<newsize;i++){
		printf("%d ",*cntr);
		cntr++;
	}
	printf("\n");
	//-------------------
	
	cntr=uj+size;	//pozíció az első új elemre
	printf("size: %d newsize: %d\n",size, newsize);
	
	for(int i=size; i<newsize; i++){
		printf("%d",*cntr);
		*cntr=0;
		printf("->%d\n",*cntr);	
		cntr++;
	}
	cntr=uj;
	printf("elso: %d\n",*cntr);
	printf("cucc1: \n");
	for (int i=0; i<newsize;i++){
		printf("%d ",*cntr);
		cntr++;
	}
	printf("\n");
	return uj;
}
//--------------------MAIN-------------------------------------------
int main() {
	int size1=5, size2=1;
	int*arr1 = (int*) calloc(size1,sizeof(int));
	int*cntr=arr1;
	for (int i=0; i<size1;i++){
		*cntr=20+i;
		printf("%d ",*cntr);
		cntr++;
	}
	int* arr2=resize(arr1,size1,size2);
	
	printf("ki: \n");
	cntr=arr2;
	for (int i=0; i<size2;i++){
		printf("%d ",*cntr);
		cntr++;
	}
	printf("\n");
	free(arr2);
	
  return 0;
}
