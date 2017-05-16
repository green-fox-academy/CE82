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
	uint8_t PORTB =  0b10111111;
	uint8_t PORTB2 = 0b10111111;
	uint8_t y =      0b00001000;
	//number ^= 1 << x;
	                            //number = !(1 << x);
	//PORTB2 = PORTB & ~( 1<<5);
	PORTB2 = PORTB & ~(y);
	
	//printf("----> PORTB2^=  1<<y;\n");
	kiirbinaris(PORTB);
	//kiirbinaris(y);
	printf("--------\n");
	kiirbinaris(PORTB2);
  
 
	
	return 0;
}
