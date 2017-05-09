#include <stdio.h>
#include <stdint.h>
uint8_t po(uint8_t alap, uint8_t kitevo){
	if (kitevo==0) return 1;
	uint8_t x=alap;
	for (int i=1; i<kitevo;i++){
		x*=alap;
	}
	return x;
}
void kiirbinaris(uint8_t mit){
	for(int i=7;i>=0;i--){
		if(mit>=po(2,i)){   
			printf("1");
			mit-=po(2,i);
		}else {printf("0");}		
	}
	printf("\n");
}
int main() {
    uint8_t x = 0b11001100;
    uint8_t y = 0b01010101;
	uint8_t z;

	// Be z equal to the bitwise and of x and y
	z=x&y;
	// Check the result with printf
	printf("and\n");
	
	kiirbinaris(x);
	kiirbinaris(y);
	printf("--------\n");
	kiirbinaris(z);
    //printf("%b\n %b \n %b",x,y,z);
	// Be z equal to the bitwise or of x and y
    z=x|y;
    printf("\n");
    printf("or\n");
    
	kiirbinaris(x);
	kiirbinaris(y);
	printf("--------\n");
	kiirbinaris(z);
	// Check the result with printf
	
    return 0;
}
