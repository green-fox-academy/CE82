/*
Write a program that reads a number form the standard input,
than prints "Odd" if the number is odd, or "Even" it it is even.
*/
#include <stdio.h>
int main(){
	int i;
	printf ("num: ");
	scanf ("%d",&i);
	if(i%2==0){
		printf("even\n");
	}else{
		printf("odd\n");
	}
}
