#include <stdio.h>
#include <stdlib.h>
int abs(x) {
	int a=x;
	if(x<0) a*=-1;
	return a;
}
int size(int to, int from, int step){
	return abs((to-from)/step);
}
int* range(int from, int to,int step) {	
	int*re = (int*) calloc(size(to, from,step) , sizeof(int));
	int*arr=re;
	if(to>=0){
		for (int i=from; i<to;i+=step){
			*arr=i;
			arr++;
		}
	}else {
		for (int i=from; i>to;i+=step){
			*arr=i;
			arr++;
		}
	}
	return re;
}
int main() {	
	int*arr =range(1, -8, -3);	
	int*p=arr;
	for (int i=0;i<size(1, -8, -3);i++){
		printf("%d ",*arr);
		arr++;
	}
	free(p);	
	return 0;
}
/** TODO:
 * Create a function called "range" that creates a new array and returns a pointer to it.
 * It should fill the array with numbers based on it's paramters.
 * It should take 3 paramters:
 * int from: the first number in the array
 * int to: it will fill the array till it would reach this number (so this number is not in the array)
 * int step: the step between the numbers
 *
 * Examples:
 * range(0, 10, 2) -> {0, 2, 4, 6, 8}
 * range(1, -8, -3) -> {1, -2, -5}
 *
 * It should delete any dynamically allocated resource before the program exits.
 */


