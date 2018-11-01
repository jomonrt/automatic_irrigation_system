/*
 * eeprom.c
 *
 * Created: 23-12-2016 10:10:50 AM
 *  Author: JOMON THOMAS
 */ 
#include <avr/eeprom.h>
#include "eeprom.h"

uint8_t eeprom_read(uint8_t location)
{
	
	uint8_t byteRead = eeprom_read_byte((uint8_t*)location); // read the byte in location 23
	return byteRead;
}


void eeprom_write(uint8_t location, uint8_t data)
{
	
	eeprom_write_byte ((uint8_t*) location, data); //  write the byte 64 to location 23 of the EEPROM 
	
	
}