//
// FILENAME: UART.c
//
// description: This file has all the functionality to transmit and receive data
// over UART. This includes characters, strings, and 8 and 16 bit integers. Integers
// are limited because I avoid using heap memory. 
//
// Written by Marek Newton
//

#include <avr/io.h>
#include <stdint.h>

#include "UART.h"

char digit_to_character(uint8_t digit)
{
    return (char)(digit + '0');
}

// This function sets up all the registers that are needed for UART communication.
void setup_UART(void)
{
    // set baud rate 
    UBRR0H = (unsigned char)(MYUBRR>>8);
    UBRR0L = (unsigned char)MYUBRR;
    // enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Set frame format to 8 data bits, 2 stop bits
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// This function transmits a single character. 
void UART_transmit_char(char data)
{
    // Wait for empty transmit buffer
    while (!( UCSR0A & (1<<UDRE0)));
    // Put data into buffer, sends the data
    UDR0 = data;
}

// This function transmits an array of characters.
void UART_transmit_string(char *string)
{
    unsigned int i;
    while(1)
    {
        char character = *(string + i);
        UART_transmit_char(character);

        if(character == '\0')
        {
            break;
        }
        i++;
    }
}

// This function transmits an 8 bit unsigned integer.
void UART_transmit_uint8_t(uint8_t number)
{
    uint8_t digit_stack[DIGIT_COUNT_8_BIT] = {0};
    uint8_t i = 0;

    while(number > 0)
    {
        uint8_t digit = number % INTEGER_BASE;
        number /= INTEGER_BASE;
        digit_stack[DIGIT_COUNT_8_BIT - i - 1] = digit;
        i++;
    }

    uint8_t leading_zero = 1;

    for(i = 0; i < DIGIT_COUNT_8_BIT; i++)
    {
        // Don't transmit leading zeros.
        if(digit_stack[i] == 0 && leading_zero && i != DIGIT_COUNT_8_BIT - 1)
        {
            continue;
        }
        else if(digit_stack[i] != 0)
        {
            leading_zero = 0;
        }

        UART_transmit_char(digit_to_character(digit_stack[i]));
    }
}

// This function transmits a 16 bit unsigned integer.
void UART_transmit_uint16_t(uint16_t number)
{
    uint8_t digit_stack[DIGIT_COUNT_16_BIT] = {0};
    uint8_t i = 0;

    while(number > 0)
    {
        uint8_t digit = number % INTEGER_BASE;
        number /= INTEGER_BASE;
        digit_stack[DIGIT_COUNT_16_BIT - i - 1] = digit;
        i++;
    }

    uint8_t leading_zero = 1;

    for(i = 0; i < DIGIT_COUNT_16_BIT; i++)
    {
        // Don't transmit leading zeros.
        if(digit_stack[i] == 0 && leading_zero && i != DIGIT_COUNT_16_BIT - 1)
        {
            continue;
        }
        else if(digit_stack[i] != 0)
        {
            leading_zero = 0;
        }

        UART_transmit_char(digit_to_character(digit_stack[i]));
    }
}

// This function transmits a 32 bit unsigned integer.
void UART_transmit_uint32_t(uint32_t number)
{
    uint8_t digit_stack[DIGIT_COUNT_32_BIT] = {0};
    uint8_t i = 0;

    while(number > 0)
    {
        uint8_t digit = number % INTEGER_BASE;
        number /= INTEGER_BASE;
        digit_stack[DIGIT_COUNT_32_BIT - i - 1] = digit;
        i++;
    }

    uint8_t leading_zero = 1;

    for(i = 0; i < DIGIT_COUNT_32_BIT; i++)
    {
        // Don't transmit leading zeros.
        if(digit_stack[i] == 0 && leading_zero && i != DIGIT_COUNT_32_BIT - 1)
        {
            continue;
        }
        else if(digit_stack[i] != 0)
        {
            leading_zero = 0;
        }

        UART_transmit_char(digit_to_character(digit_stack[i]));
    }
}

// This function receives a single character.
char UART_receive_character(void)
{
    // wait for data
    while(!(UCSR0A & (1 << RXC0)));

    // return data
    return UDR0;
}