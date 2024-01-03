#ifndef HT16K33_H
#define HT16K33_H

#include <stdint.h>

#define HT16K33_ADDRESS 0x70 
#define ON 0x21
#define STANDBY 0x20
#define DISPLAY_ON 0x81
#define DISPLAY_OFF 0x80
#define DIM 0xE0

#define DIGIT_COUNT 4
#define MAX_DIGIT 9
#define MAX_BRIGHTNESS_SETTING 15
#define SET_DIGIT_BYTE_COUNT 3
#define MAX_INTEGER 9999

void setup_HT16K33(void);
void set_brightness_HT16K33(uint8_t brightness);
void write_digit_HT16K33(uint8_t position, uint8_t number);
void display_integer(uint16_t number);

#endif
