#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t number = 254;
	uint8_t result;

	result = number + 23;
	// Check the result with printf
	printf("%d\n",result);

 	// What happened?!
	// Try again with different datatype
	uint16_t result_16 = number + 23;
	// Check the result with printf
	printf("%d\n",result_16);

	// What happened and why?
	//túlcsordult
	//----------------------------------------
	int8_t number_negative = number;
	// Check the result with printf
	printf("%d %d\n",number_negative, number);

	// What happened and why?
	//az egyik bit előjelet ábrázol
    return 0;
}
