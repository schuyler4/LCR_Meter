#ifndef HT16K33_H
#define HT16K33_H

#include <stdint.h>
#include "hardware/i2c.h"

#define HT16K33_ADDRESS 0x70 
#define ON 0x21
#define STANDBY 0x20
#define DISPLAY_ON 0x81
#define DISPLAY_OFF 0x80
#define DIM 0xE0
#define ROW_INT 0xA0

#define DIGIT_COUNT 4
#define MAX_DIGIT 9
#define MAX_BRIGHTNESS_SETTING 15
#define SET_DIGIT_BYTE_COUNT 3
#define MAX_INTEGER 9999
#define COLON_INDEX 2
#define ZERO_NUMBER 10

void setup_HT16K33(i2c_inst_t* i2c_handler);
void set_brightness_HT16K33(uint8_t brightness, i2c_inst_t* i2c_handler);
void write_digit_HT16K33(uint8_t position, uint16_t number, i2c_inst_t* i2c_handler);
void display_integer(uint16_t number, i2c_inst_t* i2c_handler);

#endif
