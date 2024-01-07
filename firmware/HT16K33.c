#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "HT16K33.h"

static const uint16_t number_table[] = {  
    0xC3F,
    0x406,
    0x5b,
    0x4f,
    0x66,
    0x6d,
    0x7d,
    0x07,
    0x7f,
    0x67,
    0x00
};

static void i2c_write_byte(uint8_t byte, i2c_inst_t* i2c_handler)
{
    i2c_write_blocking(i2c_handler, HT16K33_ADDRESS, &byte, 1, 0); 
}

void setup_HT16K33(i2c_inst_t* i2c_handler)
{
    i2c_write_byte(ON, i2c_handler);
    i2c_write_byte(DISPLAY_ON, i2c_handler);    
}

void set_brightness_HT16K33(uint8_t brightness, i2c_inst_t* i2c_handler)
{
    if(brightness <= MAX_BRIGHTNESS_SETTING)
    {
        i2c_write_byte(DIM | brightness, i2c_handler);
    }
}

void write_digit_HT16K33(uint8_t position, uint16_t number, i2c_inst_t* i2c_handler)
{
    if(number <= MAX_DIGIT + 1 && position <= DIGIT_COUNT)
    {
        uint8_t buffer[SET_DIGIT_BYTE_COUNT];
        buffer[0] = position * 2;
        buffer[1] = number_table[number] & 0xFF;
        buffer[2] = number_table[number]  >> 8;
        i2c_write_blocking(i2c_handler, HT16K33_ADDRESS, buffer, SET_DIGIT_BYTE_COUNT, 0);
    } 
}

void display_integer(uint16_t number, i2c_inst_t* i2c_handler)
{
    write_digit_HT16K33(COLON_INDEX, ZERO_NUMBER, i2c_handler); 
    uint16_t my_number = number;
    if(number <= MAX_INTEGER)
    {
        int8_t digit_index = DIGIT_COUNT;
        while(my_number > 0 || digit_index >= 0)
        {
            if(digit_index == COLON_INDEX)
            {
                digit_index--;
                continue;
            }

            if(my_number > 0)
            {
                uint16_t digit = my_number % 10;
                write_digit_HT16K33(digit_index, digit, i2c_handler);  

                my_number /= 10;
            }
            else
            {
                write_digit_HT16K33(digit_index, 0, i2c_handler);  
            }
            digit_index--;
        }    
    } 
}
