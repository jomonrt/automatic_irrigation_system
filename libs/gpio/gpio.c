/*
 * gpio.c
 *
 * Created: 22-12-2016 11:59:23 PM
 *  Author: JOMON THOMAS
 */ 
#include "avr/io.h"

void set_pin_on(int port, int pin)
{

	port |= (1 << pin);
	
}

void set_pin_off(int port, int pin)
{
	
	port &= ~(1 << pin);
	
}