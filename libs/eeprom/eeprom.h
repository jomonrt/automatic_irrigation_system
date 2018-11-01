/*
 * eeprom.h
 *
 * Created: 23-12-2016 10:11:03 AM
 *  Author: JOMON THOMAS
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

uint8_t eeprom_read(uint8_t location);

void eeprom_write(uint8_t location, uint8_t data);



#endif /* EEPROM_H_ */