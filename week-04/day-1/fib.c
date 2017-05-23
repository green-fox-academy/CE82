/* Write a function which is called "get_fibonacci_number". It returns the "N"th
 * Fibonacci number, where "N" is received as a paramter.
 * For example:
 *  - get_fibonacci_number(1) returns 0
 *  - get_fibonacci_number(2) returns 1
 *  - get_fibonacci_number(3) returns 1
 *  - get_fibonacci_number(4) returns 2
 *  - get_fibonacci_number(5) returns 3
 *  - get_fibonacci_number(6) returns 5
 *
 *  If the function gets invalid parameter it returns -1.
 */

/*
Using that function create a program, which gets a number from the user, and
prints out the "N"th Fibonacci number, where "N" is the user given number.
Alert the user if he/she entered invalid value.
*/
#include<stdio.h>
int get_fibonacci_number(int n){
	if (n==1) {
		return 0;
	}
	if(n==2){
		return 1;
	}
	if(n<1){//invalid parameter
		printf("invalid parameter!\n");
		return -1;
	}
	int x=0;
	int y=1;
	int fib=1;
	
	for (int i=2; i<n;i++){
		fib=x+y;
		x=y;
		y=fib;
	}
	return fib;
}


void main(){
	int n;
	printf ("num: ");
	scanf ("%d",&n); 
	printf("%d \n",get_fibonacci_number(n));
}

