/*
Create a program which ask for a name and an age.
From the age it tells the user when he or she will be 100 years old.
You should only take care of the years (don't bother with the months or days).
*/
#include <stdio.h>

int main ()
{
  char str [80];
  int i;

  printf ("Enter your name: ");
  scanf ("%79s",str);  
  printf ("Enter your age: ");
  scanf ("%d",&i); //  scanf ("%d",&i);
  printf ("Ekkor leszel 100 éves: %d\n",(2017-i)+100);
  
  
  return 0;
}

