/*
 * uart.c
 *
 * Created: 24-12-2016 10:28:51 PM
 *  Author: JOMON THOMAS
 */ 

#define F_CPU 4000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#include "uart.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
//#include <util/setbaud.h>

void initUSART(void) 
{             
	                       /* requires BAUD */
	//UBRRH = UBRRH_VALUE;                        /* defined in setbaud.h */
	//UBRRL = UBRRL_VALUE;
	UBRRH = (BAUDRATE >> 8);
	UBRRL = BAUDRATE;
	#if USE_2X
	UCSRA |= (1 << U2X);
	#else
	UCSRA &= ~(1 << U2X);
	#endif
	
	UCSRB |= (1 << TXEN) | (1 << RXEN);  /* Enable USART transmitter/receiver */
	UCSRC |= (1 << URSEL)|(1 << UCSZ1) | (1 << UCSZ0);   /* 8 data bits, 1 stop bit */
}


void transmitByte(uint8_t data) {
	                                   
	loop_until_bit_is_set(UCSRA, UDRE);    /* Wait for empty transmit buffer */
	UDR = data;                                            /* send data */
}

uint8_t receiveByte(void) {
	loop_until_bit_is_set(UCSRA, RXC);       /* Wait for incoming data */
	return UDR;                                /* return register value */
}


/* Here are a bunch of useful printing commands */

void printString(const char myString[]) {
	uint8_t i = 0;
	while (myString[i]) {
		transmitByte(myString[i]);
		i++;
	}
}

void readString(char myString[], uint8_t maxLength) {
	char response;
	uint8_t i;
	i = 0;
	while (i < (maxLength - 1)) {                   /* prevent over-runs */
		response = receiveByte();
		//transmitByte(response);                                    /* echo */
		if (response == '\r') {                     /* enter marks the end */
			break;
		}
		else {
			myString[i] = response;                       /* add in a letter */
			i++;
		}
	}
	myString[i] = 0;                          /* terminal NULL character */
}

void printByte(uint8_t byte) {
	/* Converts a byte to a string of decimal text, sends it */
	transmitByte('0' + (byte / 100));                        /* Hundreds */
	transmitByte('0' + ((byte / 10) % 10));                      /* Tens */
	transmitByte('0' + (byte % 10));                             /* Ones */
}

void printWord(uint16_t word) {
	transmitByte('0' + (word / 10000));                 /* Ten-thousands */
	transmitByte('0' + ((word / 1000) % 10));               /* Thousands */
	transmitByte('0' + ((word / 100) % 10));                 /* Hundreds */
	transmitByte('0' + ((word / 10) % 10));                      /* Tens */
	transmitByte('0' + (word % 10));                             /* Ones */
}

void printBinaryByte(uint8_t byte) {
	/* Prints out a byte as a series of 1's and 0's */
	uint8_t bit;
	for (bit = 7; bit < 255; bit--) {
		if (bit_is_set(byte, bit))
		transmitByte('1');
		else
		transmitByte('0');
	}
}

char nibbleToHexCharacter(uint8_t nibble) {
	/* Converts 4 bits into hexadecimal */
	if (nibble < 10) {
		return ('0' + nibble);
	}
	else {
		return ('A' + nibble - 10);
	}
}

void printHexByte(uint8_t byte) {
	/* Prints a byte as its hexadecimal equivalent */
	uint8_t nibble;
	nibble = (byte & 0b11110000) >> 4;
	transmitByte(nibbleToHexCharacter(nibble));
	nibble = byte & 0b00001111;
	transmitByte(nibbleToHexCharacter(nibble));
}

uint8_t getNumber(void) {
	// Gets a numerical 0-255 from the serial port.
	// Converts from string to number.
	char hundreds = '0';
	char tens = '0';
	char ones = '0';
	char thisChar = '0';
	do {                                                   /* shift over */
		hundreds = tens;
		tens = ones;
		ones = thisChar;
		thisChar = receiveByte();                   /* get a new character */
		transmitByte(thisChar);                                    /* echo */
		} while (thisChar != '\r');                     /* until type return */
		return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
	}
