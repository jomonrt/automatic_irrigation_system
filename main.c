/*
 * Automatic_water.c
 *
 * Created: 22-12-2016 08:53:57 AM
 * Author : JOMON THOMAS
 */ 
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include "timer.h"
#include "gpio.h"
#include "power.h"
#include "eeprom.h"
#include "uart.h"
#include "adc.h"
#include <avr/common.h>

#define VALVE_PORT PORTB
#define VALVE_DDR DDRB
#define VALVE_PIN 1
#define EEPROM_STATUS_LOCATION 0x02
#define VALVE_ON 0x01
#define VALVE_OFF 0x00

#define ON_TIME 20   //Time in seconds
#define OFF_TIME 1  //Time in Minutes
#define ADC_CUT_OFF_VALUE 30 //ADC value cutt off

bool valve_status = VALVE_ON;


void reset_timer(void)
{
	
	set_timer_minutes(0);
	set_timer_seconds(0);
	
}


void check_previous_valve_status()
{
	
	uint8_t status = eeprom_read(EEPROM_STATUS_LOCATION);
	if(status == 0x01)
	{
		valve_status = true;
		set_bit(VALVE_PORT, VALVE_PIN);
	}
	
}

void valve_initialisation(void)
{
	set_bit(VALVE_DDR,VALVE_PIN);
	clear_bit(VALVE_PORT,VALVE_PIN);
	
}



int main(void)
{
   valve_initialisation();
   //check_previous_valve_status();
   adc_init();
   start_adc_conversion_automatic();
   timer_init();
   timer_start();
   //initUSART(); 
   //printString("Starting");
   //set_bit(ASSR,AS2);

    while (1) 
    {
		
		
		switch(valve_status)
		{
			
			case VALVE_OFF:
			    if(get_timer_minutes() >= OFF_TIME)  //off time
			    {
				    
				    //if(get_adc_value() >= ADC_CUT_OFF_VALUE)
				   // {
					    set_bit(VALVE_PORT, VALVE_PIN);
					    valve_status = VALVE_ON;
					    eeprom_write(EEPROM_STATUS_LOCATION, VALVE_ON);
				   // }
					
				    reset_timer();
				    
			    }
			
			   break;
				
			   
		    case VALVE_ON:
			    if(get_timer_seconds() >= ON_TIME)   //on time
			    {
				    clear_bit(VALVE_PORT, VALVE_PIN);
				    valve_status = VALVE_OFF;
				    eeprom_write(EEPROM_STATUS_LOCATION, VALVE_OFF);
				    reset_timer();
			    }
			    break;
		}
		
				

    }
}

