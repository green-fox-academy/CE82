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

	uint8_t ac = 8;
	uint8_t time = 233;
	uint8_t out;
	// if ac is dividable by 4
	// and time is not more than 200
	// set out to 0b100
	if(ac%4==0&&time<=200) out=0b100;
	// if time is more than 200
	// set out to 0b010
	else if(time>200) out=0b010;
	// otherwise set out to 0b001
	else out=0b010;
	kiirbinaris(out);
	return 0;
}
