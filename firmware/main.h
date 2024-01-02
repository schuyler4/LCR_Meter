#ifndef MAIN_H
#define MAIN_H

#include "pico/stdlib.h"

#define SPI_CLK_FREQUENCY 20000000
#define MOSI_PIN 7
#define MISO_PIN 8
#define CS_PIN 9
#define SCK_PIN 2
#define CONVST_PIN 10

void setup_SPI(void);
void setup_IO(void);

#endif
