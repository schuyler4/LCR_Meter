#ifndef MAIN_H
#define MAIN_H

#include "pico/stdlib.h"

#define SPI_CLK_FREQUENCY 2000000
#define I2C_CLK_FREQUENCY 1000
#define MOSI_PIN 7
#define MISO_PIN 8
#define CS_PIN 9
#define SCK_PIN 2
#define CONVST_PIN 10
#define SCL_PIN 17
#define SDA_PIN 16

void setup_SPI(void);
void setup_I2C(void);
void setup_IO(void);

#endif
