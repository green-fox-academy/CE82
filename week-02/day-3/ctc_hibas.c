#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
ISR (TIMER1_COMPA_vect){   
    PORTB ^= (1 << 5);
}
void init(){
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
// Mode = CTC, Prescaler = 64
	TCNT1 = 0;
	OCR1A = 24999;   // timer compare value
	//mert 1ms togglét akarunk
	TIMSK1=1<OCIE1A;
}
int main(void){
	DDRB |= (1 << 5);
    init();
    while (1) {
		//TIFR1 |= (1 << OCF1A);
    }
}

