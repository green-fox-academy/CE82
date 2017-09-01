#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>
#include "pwm_driver.h"
int main(void)
{
    /* Replace with your application code */
	init_pwm();
	
	uint8_t duty = 80, add = 1;
	
    while (1) 
    {	
		if (duty == 100)
			add = -1;
		if (duty == 1)
			add = 1;
		duty += add;
		set_duty_cycle(0);
		_delay_ms(1000);
		set_duty_cycle(30);
		_delay_ms(1000);
		set_duty_cycle(70);
		_delay_ms(1000);
		set_duty_cycle(100);
		_delay_ms(1000);
    }
}

