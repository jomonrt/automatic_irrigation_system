/*
 * adc.c
 *
 * Created: 24-12-2016 10:27:43 PM
 *  Author: JOMON THOMAS
 */ 
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/common.h>

volatile int adc_value = 0;


int get_adc_value(void)
{
	return adc_value;
	
}


void adc_init(void)
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1<<ADPS1)|(1 << ADPS0)|(1<<ADIE);
	sei();
}

void start_adc_conversion_automatic(void)
{
	ADMUX |= (1<<MUX0); //adc first channel
	ADCSRA |= (1<<ADSC);
	
}

int start_conversion_mannual(void)
{
	ADMUX |= (1<<MUX0);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}



ISR(ADC_vect)
{
	
	adc_value = (int)(ADC);
	
}