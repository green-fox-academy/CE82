#include <avr/io.h>
#include "AC_driver.h"
#include "UART_driver.h"
#include "pwm_driver.h"
 volatile uint16_t cnt = 0;
 volatile double ford_time = 0;
void AC_driver_init()
{
	/*************
	 * AC CONFIG *
	 *************/
	//		TODO:
	//		Disable the digital input buffers on AN0 and AN1 to reduce power consumption.
	//		See the DIDR1 register description for more info.
	
	DIDR1 |= (1 << AIN1D) | (1 << AIN0D);
	//		TODO:
	//		Connect the AC output to the AC0 pin.
	//AC0- pin ??? van egy, amit ACO-nak hívnak, ua  PE0	
	//		The datasheet if screwed up. It says "Analog Comparator Control and Status Register C", meanwhile the name of 
	//		this register is "ACSR0",
	//		but in the avr/io.g header this register can be reached with the "ACSRB" macro.

	//		TODO:
	//		Configure the rest settings properly :)
	//		AC output connected to TC1 input capture
	ACSRB |= (1 << ACOE); 
	
	//When this bit is set, the analog comparator output is connected to the ACO pin.
	// ???????????????????????????
	//ACO: ACSR bitje, The output of the Analog Comparator is synchronized and then directly connected to ACO. The 
	//synchronization introduces a delay of 1 - 2 clock cycles.
//bemeneti pinek	
	//AIN0, AIN1: PD6, PD7
	/*
	positive pin AIN0 and negative pin AIN1.
	AIN0 >  AIN1, ACO is set.
	*/
	DDRB |= 1<<DDRB5; //led kimenet 
	PORTB|= 1 << 5; //led bekapcs initkor
	
	DDRE |= (1<<DDRE0);
	DDRD &= ~(1<<DDRD6);
	DDRD &= ~(1<<DDRD7);
			//we convert this analog signal to a digital signal, which can trigger an input capture event in the TC1 timer.
	
	/* 
	The comparator’s output can be set to trigger the Timer/Counter1 Input
	Capture function. In addition, the comparator can trigger a separate interrupt, exclusive to the Analog
	Comparator.
	
	ACSR ACIC
	When written logic one, this bit enables the input capture function in Timer/Counter1 to be triggered by
	the Analog Comparator. The comparator output is in this case directly connected to the input capture
	front-end logic, making the comparator utilize the noise canceler and edge select features of the Timer/
	Counter1 Input Capture interrupt. When written logic zero, no connection between the Analog
	Comparator and the input capture function exists. To make the comparator trigger the Timer/Counter1
	Input Capture interrupt, the ICIE1 bit in the Timer Interrupt Mask Register (TIMSK1) must be set.
	
	TIMSK1:ICIE1: Input Capture Interrupt Enable
	When this bit is written to '1', and the I-flag in the Status Register is set (interrupts globally enabled), the
	Timer/Counter1 Input Capture interrupt is enabled. The corresponding Interrupt Vector is executed when
	the ICF Flag, located in TIFR1, is set
	
	Timers in AVR have input pins to trigger the input capture event. A signal change at such a pin causes the
	timer value to be read and saved in the Input Capture Register (ICRx). At the same time the Input
	Capture Flag (ICFx) in the TIFRn will be set. This is useful to measure the width of external pulses.
	
	When a change of the logic level (an event) occurs on the Input Capture pin (ICP1), or alternatively on the
	Analog Comparator output (ACO), and this change confirms to the setting of the edge detector, a capture
	will be triggered: the 16-bit value of the counter (TCNT1) is written to the Input Capture Register (ICR1).
	*/
	//azaz az interruptban az ICR1-et olvasom és kész
	ACSR |= (1 << ACIC); //enables the input capture function in Timer/Counter1 to be triggered by the Analog Comparator
	//to make the comparator trigger the Timer/Counter1	Input Capture interrupt, 
	//the ICIE1 bit in the Timer Interrupt Mask Register (TIMSK1) must be set.
	ACSR |= (1 << ACIE); //analog Comparator Interrupt Enabl
	ACSR &= ~(1 << ACD) ; //disable ki, bandgap ki
	ACSR &= ~(1<<ACBG);
	//ötös bit ACO, compare eredménye
	//négyes ACI: Analog Comparator Interrupt Flag, hardware állítja be interruptkor
	ACSR |= (1 << ACIS0);
	ACSR &= ~(1 << ACIS1); //Comparator Interrupt on Falling Output Edge.

	TIMSK1 |= (1 << ICIE1) | (1 << TOIE1);
	TIMSK1 &= ~(1 << OCIE1B) ; 
	TIMSK1 &= ~(1 << OCIE1A) ;//compare disabled
	// így TIFR1-bõl csak ICF1 használható
	sei();	
	
	TCCR1B &= ~(1 << ICES1); //when the ICES1 bit is	written to '1', a rising (positive) edge will trigger the capture.
	TCCR1B |= (1 << CS10); //prescale 0
	TCCR1B &= ~(1 << CS12) | ~(1 << CS11);
	
}
ISR(TIMER1_OVF_vect){
	
	cnt ++;
	if (cnt == 65535)
		cnt = 0;
}

ISR(TIMER1_CAPT_vect)
{	
	
	ford_time = cnt * (65536) + ICR1; 
	cnt = 0;
	//UART_send_character(((0b00100000 & ACSR) == 32)+48);
	if (32 == (0b00100000 & ACSR )) {
		PORTB |= 1 << 5;		
	} else {
		PORTB &= ~(1 << 5);		
	}
}
		// TODO:
		// Write this function. It returns the measured rotation speed in RPM
float get_rpm()
{
	printf("aco: %d\n", 32 == (0b00100000 & ACSR ));//ACO bit, megvan
	/*
	if (32 == (0b00100000 & ACSR )) {
		PORTB |= 1 << 5;
		} else {
		PORTB &= ~(1 << 5);
	}
*/
	return 0;

}