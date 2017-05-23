#include <stdio.h>

int main() 
{
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.
	int* ptr = NULL;
    ptr = hight_number_pointer;
	hight_number_pointer = low_number_pointer;
	low_number_pointer = ptr;
	printf("high..: %d \n ", *hight_number_pointer);
	printf("low..: %d \n ", *low_number_pointer);
	
	//oké, ez most ugyanaz, de már az előbb sem használtam azt a két változót
    return 0;
}
