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
