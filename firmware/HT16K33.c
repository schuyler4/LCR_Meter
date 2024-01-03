#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "HT16K33.h"

static const uint8_t number_table[] = {
    0x6F, 
    0x42,
    0x3B,
    0x5B,
    0x56,
    0x5D,
    0x7D,
    0x43,
    0x7F,
    0x57,
    0x80,
};

static void i2c_write_byte(uint8_t byte)
{
    i2c_write_blocking(i2c_default, HT16K33_ADDRESS, &byte, 1, 0); 
}

void setup_HT16K33(void)
{
    i2c_write_byte(ON);
    i2c_write_byte(DISPLAY_ON);    
}

void set_brightness_HT16K33(uint8_t brightness)
{
    if(brightness <= MAX_BRIGHTNESS_SETTING)
    {
        i2c_write_byte(DIM | brightness);
    }
}

void write_digit_HT16K33(uint8_t position, uint8_t number)
{
    if(number <= MAX_DIGIT && position <= DIGIT_COUNT)
    {
        uint8_t buffer[SET_DIGIT_BYTE_COUNT];
        buffer[0] = position * 2;
        buffer[1] = number;
        buffer[2] = 0;
        i2c_write_blocking(i2c_default, HT16K33_ADDRESS, buffer, SET_DIGIT_BYTE_COUNT, 0);
    } 
}

void display_integer(uint16_t number)
{
    if(number <= MAX_INTEGER)
    {
        uint8_t digit_index = 0;
        while(number > 0)
        {
            uint8_t digit = number % 10;
            write_digit_HT16K33(digit_index, digit);  

            number /= 10;
            digit_index++;
        }    
    } 
}
