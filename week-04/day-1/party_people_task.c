// Write a program that asks for two numbers
// The first number represents the number of girls that comes to a party, the
// second the boys.

// It should print "The party is excellent!" if the the number of girls and
// boys are equal and there are more people coming than 20

// It should print "Quite cool party!"
// if there are more than 20 people coming but the girl - boy ratio is not 1-1

// It should print: "Average party..."
// if there are less people coming than 20

// It should print: "Sausage party"
// if no girls are coming, regardless the count of the people

#include <stdio.h>
 
int main () {

   	int g,f;
	printf ("girls: ");
	scanf ("%d",&g); 
	printf ("boys: ");
	scanf ("%d",&f); 
	if(g==f && g+f>20){
		printf("The party is excellent!\n");
	}else if(g+f>20){
		printf("Quite cool party!\n");
	}else if(g+f<20){
		printf("Average party...\n");
	}
	if(g==0){
		printf("Sausage party\n");
	}
   return 0;
}
