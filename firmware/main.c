#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"

#include "main.h"
#include "HT16K33.h"

int main(void)
{
    stdio_init_all();

    setup_IO();
    setup_SPI();
    setup_I2C();

    while(1)
    {
    }

    return 1;
}

void setup_SPI(void)
{
    spi_init(spi_default, SPI_CLK_FREQUENCY);
    gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SCK_PIN, GPIO_FUNC_SPI);
}

void setup_I2C(void)
{
    i2c_init(i2c_default, I2C_CLK_FREQUENCY); 
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
}

void setup_IO(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_init(CS_PIN);
    gpio_init(CONVST_PIN);

    gpio_set_dir(CS_PIN, GPIO_OUT);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_set_dir(CONVST_PIN, GPIO_OUT);

    gpio_put(CS_PIN, 1);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    gpio_put(CONVST_PIN, 1);
}
