#include <avr/io.h>

void init()
{
	
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	TCCR0B = (1<<CS02) | (1<<CS00);
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
//azaz ezt nem kell külön..?
	// Set the PB5 LED pin to output
	//PORTB |= 0b00100000;
	DDRB = DDRB | 0b00100000;
}
uint8_t count=0;
int main(void)
{
	// Don't forget to call the init function!
	init();

    while (1){		
		// If TC0 counter overflow occurred (TOV0 flag is set) toggle the LED and write "1" to that flag (this will clear it, i know, it's confusing, but this is how does it work)
		//tényleg túl gyors volt, így nem látom, hogy jó a kód vagy nem. Csináltam egy 8-as osztást.
		//hm, azt hiszem véletlenül megcsináltam a második feladatot. 
		while (! (TIFR0 & (1<<TOV0))){} //spin till overflow
			TIFR0 |= (1<<TOV0);           //clear by writing a one to TOV0
			count++;                     //extend counter
		if((count % 8) == 0){PORTB ^= 1 << 5;}    
		
		//ez itt a butábbik kód:
		/*if((TIFR0 & 0x1) == 0){
			TIFR0 |= (1<<TOV0);
			PORTB^= 1 << 5;
		
		}
		*/
		
		
    }
}