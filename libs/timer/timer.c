/*
 * timer.c
 *
 * Created: 22-12-2016 10:30:48 PM
 *  Author: JOMON THOMAS
 */ 
#include "avr/io.h"
#include "timer.h"
#include <avr/interrupt.h>
#include "adc.h"
#include <avr/common.h>



struct Timer
{
	volatile int seconds;
	volatile int minutes;
	volatile int adc_second;
	
}timer;



int get_timer_seconds(void)
{
	return timer.seconds;
}

int get_timer_minutes(void)
{
	return timer.minutes;
}

void set_timer_seconds(int time)
{
	timer.seconds = time;
}


void set_timer_minutes(int time)
{
	timer.minutes = time;
}



unsigned int TIM16_ReadTCNT1(void)
{
	
	unsigned char sreg;
	unsigned int i;
	/* Save global interrupt flag */
	//sreg = 0x3F;
	/* Disable interrupts */
	
	
}


void timer_init(void)
{
	
	TCCR1A = 0x00; //clearing control register A
	TCCR1B = 0x00;// clearing control register B
	TCNT1 = 0x00; //clearing counter register

    TCCR1B |= (1 << WGM12); //setting CTC mode for OCR1A as top
	OCR1A = 62501;     // setting top value OCR1A at 1MHz
	TIMSK |= (1 << OCIE1A ); //output compare match a enabled
	sei();
	
}

//Function for starting the timer
void timer_start(void)
{
	
	TCCR1B |= (1 << CS10)|(1 << CS11); //Selecting clock 
	
}


//timer 1 isr
ISR(TIMER1_COMPA_vect)
{

    timer.seconds++;
	timer.adc_second++;

	if(timer.seconds >= 60)  //Checking 1 mint
	{
		timer.seconds = 0;
		timer.minutes++;
	}

	if(timer.adc_second == 120) // Checking ADC conversion time
	{
		timer.adc_second =0;
		start_adc_conversion_automatic();	
	}
	
}


