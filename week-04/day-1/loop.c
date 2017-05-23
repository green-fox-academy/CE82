/*
Create a program which writes down the following sentence 100 times:
"I won't cheat on the test!"
Do it with:
    - for loop
    - while loop
    - do while loop
Also create a funtion which does the same.
*/
#include <stdio.h>
int main(){
	for (int i=0; i<100; i++){
		printf("I won't cheat on the test!\n");
	}
	int i=0;
	while(i<100){
		printf("I won't cheat on the test! %d \n",i+1);
		i++;
	}
	i=0;
	do{
		printf("I won't cheat on the test!%d \n",i+1);
		i++;
	}while(i<100);
	
	return 0;
}
