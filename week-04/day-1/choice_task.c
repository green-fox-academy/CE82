//make it work
#define MAX_DIGITS 20
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int main(){
	int number=1;
	int choice=0;
	printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
	printf("- for it's memory address please press 1\n");
	printf("- for it's current value please press 2\n");
	printf("- to double it's value please press 3\n");
	char term;
	int val;
	int okay = 0;
	while (choice!=4){	
		printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
		printf("- for it's memory address please press 1\n");
		printf("- for it's current value please press 2\n");
		printf("- to double it's value please press 3\n");
		printf("- to exit please press 4\n");
		//scanf ("%d",&choice);
		
		do{
			char input[MAX_DIGITS+2]; // +1 for sign, +1 for 0 terminator			
			if (fgets(input, sizeof input, stdin)){
				char *chk = NULL; // points to the first character *not* converted by strtol
				val = (int) strtol(input, &chk, 10);
				if (isspace(*chk) || *chk == 0)	{
					// input was a valid integer string, we're done
					choice=val;
					okay = 1;
				}
				else{
					printf(" is not a valid integer string, try again.\n");
				}
			}
		} while (!okay);
		
		switch(choice) {
		  case 1 :
			 printf("%x\n",&number);
			 break;
		  case 2 :
		  	 printf("%d\n",number );
			 break;
		  case 3 :
			 printf("double: %d\n", number*2 );
			 break;
		  case 4 :
			 printf("exit\n");
			 break;
		  default :
			 printf("nem jo valasztas\n" );
	   }
	   
	  
   }
	return 0;
}
