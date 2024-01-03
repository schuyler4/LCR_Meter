#ifndef MAIN_H
#define MAIN_H

#include "pico/stdlib.h"

#define SPI_CLK_FREQUENCY 20000000
#define I2C_CLK_FREQUENCY 100000
#define MOSI_PIN 7
#define MISO_PIN 8
#define CS_PIN 9
#define SCK_PIN 2
#define CONVST_PIN 10
#define SCL_PIN 21
#define SDA_PIN 20

void setup_SPI(void);
void setup_I2C(void);
void setup_IO(void);

#endif
