//
// FILENAME: UART.h
//
// description: this file contains the prototypes for the UART functions. 
//
// Written by: Marek Newton
//

#ifndef UART_H
#define UART_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define BAUD 9600
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)

#define INTEGER_BASE 10

#define DIGIT_COUNT_8_BIT 3
#define DIGIT_COUNT_16_BIT 5
#define DIGIT_COUNT_32_BIT 10

#define NEW_LINE_AND_CARRIAGE_RETURN "\n\r" 
#define NEW_LINE "\n"

// This function should be called before any UART functions are used.
void setup_UART(void);

void UART_transmit_char(char data);
void UART_transmit_string(char *string);
void UART_transmit_uint8_t(uint8_t number);
void UART_transmit_uint16_t(uint16_t number);
void UART_transmit_uint32_t(uint32_t number);
char UART_receive_character(void);

#endif