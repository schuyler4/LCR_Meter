#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"

#include "main.h"
#include "HT16K33.h"
#include "ADS8328.h"

static i2c_inst_t *i2c = i2c0;

int main(void)
{
    stdio_init_all();

    setup_SPI();
    setup_I2C();
    setup_IO();

    setup_ADS8328();
    setup_HT16K33(i2c);

    set_brightness_HT16K33(6, i2c);
    //select_ADS8328_channel(1);

    while(1)
    {
        //uint16_t result = ADS8328_read_config_register(); 
        //printf("%d\n", result);
        gpio_put(CONVST_PIN, 0);
        sleep_us(1);
        gpio_put(CONVST_PIN, 1);
        sleep_ms(1000);
    }
    
    return 1;
}

void setup_SPI(void)
{
    spi_init(spi0, SPI_CLK_FREQUENCY);
    gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SCK_PIN, GPIO_FUNC_SPI);
}

void setup_I2C(void)
{
    i2c_init(i2c, I2C_CLK_FREQUENCY); 
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

    gpio_pull_up(SCL_PIN);
    gpio_pull_up(SDA_PIN);
}
