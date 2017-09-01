#include "pwm_driver.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

void init_pwm()
{
	/*
			you will set the TC0 timer to Fast PWM mode to generate PWM signals on the OC0A pin of the MCU.	
			Write a function which initializes the TC0 timer in Fast PWM mode
	OC0A : Output Compare pin
	OCRA : Output Compare Register
	
	Mode	WGM02	WGM01	WGM00	Timer/Counter Mode of Operation		TOP		Update of OCR0x at	TOV Flag Set on
	3		0		1		1		Fast PWM							0xFF	BOTTOM (= 0x00)		MAX (= 0xFF)
	7		1		1		1		Fast PWM							OCRA	BOTTOM				TOP
	 Data Direction Register (DDR) bit corresponding to the OC0A pin must be set in order to enable the output driver.
	*/
	//DDRB |= 1 << DDRB0;
	DDRD |= (1 << DDRD6);	//D6 output
	//PORTD |= (1 << PORTD6);//teszt
	
	TCCR0A |= (1 << WGM00) | (1 << WGM01); //fast pwm
	TCCR0B  &= ~ (1 << WGM02)  ;// ??????????????????????????????????????????????? de így mûködik
	TCCR0B |= (1 << CS00); //van clock
	TCCR0B &= ~ (1 << CS01);//no prescaling
	TCCR0B &= ~ (1 << CS02);//no prescaling
	//non-inverting:
	TCCR0A |= (1 << COM0A1) ; 
	TCCR0B &= ~  (1 << COM0A0); 
	/*
	if one or both of the COM0A[1:0] bits are set, the OC0A output overrides the normal port functionality 
	of the I/O pin it is connected to. However, note that the Data Direction Register (DDR) bit corresponding
	to the OC0A pin must be set in order to enable the output driver.
	When OC0A is connected to the pin, the function of the COM0A[1:0] bits depends on the WGM0[2:0] bit
	setting. The table below shows the COM0A[1:0] bit functionality when the WGM0[2:0] bits are set to a
	normal or CTC mode (non- PWM)
	
	Compare Output Mode, Fast PWM:
	COM0A1	COM0A0	Description
	0		1		WGM02 = 0: Normal Port Operation, OC0A Disconnected
					WGM02 = 1: Toggle OC0A on Compare Match
	1		0		Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
	1		1		Set OC0A on Compare Match, clear OC0A at BOTTOM (inverting mode)
	*/
	//TIMSK0 |= (1 << OCIE0A); //hátha kell
	sei();
	
	
	
}
void set_duty_cycle(uint8_t value)
{
	if (value > 100 || value < 0)
		return;
	uint16_t tmp = (255 * value);
	OCR0A = tmp/100;
/*
		Write a function which sets the duty cycle (0-100) of the PWM signal on the OC0A pin
		The function should have one uint8_t parameter which value is between 0-100
		Try out the init function and the duty cycle setter function
		You should change the light intensity of the LEDs

TOP is defined as OCR0A when WGM0[2:0]=0x7.
*/


}


/*
TCCR0B Bits 2:0 – CS0n: Clock Select [n = 0..2]
The three Clock Select bits select the clock source to be used by the Timer/Counter
CS02	CS01	CS00	Description
0		0		0		No clock source (Timer/Counter stopped).
0		0		1		clk I/O/1 (No prescaling)
0		1		0		clk I/O/8 (From prescaler)
0		1		1		clkI/O/64 (From prescaler)
1		0		0		clkI/O/256 (From prescaler)
1		0		1		clkI/O/1024 (From prescaler)
1		1		0		External clock source on T0 pin. Clock on falling edge.
1		1		1		External clock source on T0 pin. Clock on rising edge.
*/

