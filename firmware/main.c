#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "main.h"

int main(void)
{
    stdio_init_all();

    setup_IO();
    setup_SPI();

    printf("Hello UART\n");

    while(1)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        printf("GOD\n");
        sleep_ms(1000);


        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        printf("LED OFF\n");
        sleep_ms(1000);
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
