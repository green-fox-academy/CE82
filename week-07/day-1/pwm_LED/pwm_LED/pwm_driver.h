#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_
#endif /* PWM_DRIVER_H_ */
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
void init_pwm();
void set_duty_cycle(uint8_t value);

