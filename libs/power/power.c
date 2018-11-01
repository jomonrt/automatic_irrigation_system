/*
 * power.c
 *
 * Created: 22-12-2016 10:30:48 PM
 *  Author: JOMON THOMAS
 */ 
#include <avr/sleep.h>
#include <avr/interrupt.h>

void power_down(void)
{
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	sleep_enable();
	//sleep_bod_disable();
	sei();
	sleep_cpu();
	
	sleep_disable();
	sei();
	
}