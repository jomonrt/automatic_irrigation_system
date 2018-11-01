/*
 * gpio.h
 *
 * Created: 22-12-2016 11:59:55 PM
 *  Author: JOMON THOMAS
 */ 


#ifndef GPIO_H_
#define GPIO_H_


/* Define up the full complement of bit-twiddling macros */
#define BV(bit)               (1 << bit)
#define set_bit(sfr, bit)     (_SFR_BYTE(sfr) |= BV(bit))  // old sbi()
#define clear_bit(sfr, bit)   (_SFR_BYTE(sfr) &= ~BV(bit)) // old cbi()
#define toggle_bit(sfr, bit)  (_SFR_BYTE(sfr) ^= BV(bit))


void set_pin_off(int port, int pin);

void set_pin_on(int port, int pin);


#endif /* GPIO_H_ */