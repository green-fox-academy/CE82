#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a struct called CircularBuffer
// It should store:
// A pointer that points to the start of a dynamically allocated array of ints (could be null) (head pointer)
// A pointer that points to the end of the dynamically allocated array of ints (could be null) (tail pointer)
// A pointer that points to the currently readable buffer item (could be null) (read pointer))
// A pointer that points to the currently writable buffer item (could be null) (write pointer)
// The lenght of the buffer

typedef struct{
    int *start;
    int *end;
    int *read;
    int *write;
    int len;
}CircularBuffer;

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer (the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and it's length as argument, and it should fill all the buffer values from the array

CircularBuffer *konstr(int *arr, int l)
{
	CircularBuffer *cb;
	int *a;
	a=arr;
	cb=malloc(sizeof (CircularBuffer));
	cb->len=l;
	cb->start=calloc(l, sizeof (int));
	cb->write = cb->start;
	int *ptr;
	ptr = cb->write;
	for (int i=0; i<l; i++){
		*ptr=*a;
		//printf(" plus ");
		ptr++;
		a++;
	}
	cb->end = ptr;
	//printf("::: %d\n",(cb->end - cb->start) / sizeof (int));
	cb->write = cb->start;//talán nem ide...
	cb->read = cb->start;
	return cb;
}


// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffers length and reallocate it's array as well. (copying it's values)

CircularBuffer *resize(CircularBuffer *cb, int newsize)
{
	int *a, *arr, *ptr;
	
	//újrahúzom
	cb->len = newsize;
	cb->start = realloc(cb->start, newsize * sizeof (int));
	cb->write = cb->start;
	cb->read = cb->write;
	cb->end = cb->start + newsize;
	return cb;
}


// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer

CircularBuffer *constr_even(CircularBuffer *cb)
{
	CircularBuffer *new_cb;
	new_cb=malloc(sizeof (CircularBuffer));
	
	//számolok
	int *ptr, *a;
	ptr = cb->start;
	new_cb->len = 0;
	for (int i=0; i < cb->len; i++){
		if(*ptr % 2 == 0){
			new_cb->len++;
		}			
		ptr++;		
	}
	//printf("even: %d\n",new_cb->len);
	//megvan a hossz. Most létrehozom
	new_cb->start=calloc(new_cb->len, sizeof (int));
	new_cb->write = new_cb->start;
	new_cb->read = new_cb->start;
	new_cb->end = new_cb->start + new_cb->len;
	
	//bemásolom az even értékeket
	ptr = cb->start;
	a = new_cb->start;
	for (int i=0; i<cb->len; i++){
		//printf("-- %d", *ptr);
		if(*ptr % 2 == 0){
			*a=*ptr;
			a++;
			//printf(" plus ");
		}			
		ptr++;		
	}
	return new_cb;
}

// TODO:
// Try all the functions in the main function, plase deallocate any buffer and the array inside it after using them

int main() 
{	
	int arr[]={1,3,2,6,9,2,2,2}, *a;
	a=&arr;
	CircularBuffer *cb;
	cb=konstr(a, 8);	
	for(int i=0; i<8; i++) {
		printf("%d ",*a);
		a++;
	}
	printf("\n");
	//printf("%d\n",(cb->end - cb->start) / sizeof (int));
	while(cb->read != cb->end) {
		a = cb->read;
		printf("%d ", *a);
		cb->read++;
	}
	printf("\n");
	cb->read = cb->start;
	
	cb=resize(cb,10);
	while(cb->read != cb->end) {
		a = cb->read;
		printf("%d ", *a);
		cb->read++;
	}
	printf("\n");
	
	CircularBuffer *even_cb;
	even_cb = constr_even(cb);
	while(even_cb->read != even_cb->end) {
		a = even_cb->read;
		printf("%d ", *a);
		even_cb->read++;
	}
	printf("\n");
	free(cb->start);
	free(cb);
	free(even_cb->start);
	free(even_cb);
	return 0;
}
