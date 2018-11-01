/*
 * uart.h
 *
 * Created: 24-12-2016 10:29:07 PM
 *  Author: JOMON THOMAS
 */ 


#ifndef UART_H_
#define UART_H_
#include <stdint.h>




void initUSART(void) ;

void printString(const char myString[]);
void transmitByte(uint8_t data);



#endif /* UART_H_ */