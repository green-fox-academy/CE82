#include <stdio.h>

/* Write a non void function which has a paramters (let's say for example x).
The funtion than returns the "xth" fibonaci number.
What the hack is a fibonacci number? Search it on wikipedia!
*/
long fib(int xth){
	if(xth==1) return 0;
	if(xth==2) return 1;
	long x1=0;
	long x2=1;
	long x3;
	for(int i=0; i<xth-2;i++){
		x3=x1+x2;
		x1=x2;
		x2=x3;
	}
	return x3;
}
int main(){
	int a=10;
	for (int i=1; i<a;i++){
    	printf(" fib%d: %ld\n",i,fib(i));
    }
    return 0;
}
