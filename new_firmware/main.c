#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "main.h"

int main(void)
{
    stdio_init_all();
    uint16_t sample_buffer[ADC_SAMPLE_COUNT];  
    setup_GPIO();
    adc_init();
    select_range();
    adc_fifo_setup(true, false, 0, false, false);
    adc_run(true);
    uint16_t i;
    for(i=0;i<ADC_SAMPLE_COUNT;i++)
        sample_buffer[i] = adc_fifo_get_blocking();  
    adc_run(false);
    adc_fifo_drain();
    while(1)
    {
        printf("START\n");
        for(i=0;i<ADC_SAMPLE_COUNT;i++)
            printf("%d\n", sample_buffer[i]);
        printf("END\n");
    }
    // The program should never return.
    return 1;
}

void setup_GPIO(void)
{
    uint8_t i;     
    for(i = 0; i < MUX_BIT_COUNT; i++)
    {
        gpio_init(MUX_BIT0+i);
        gpio_set_dir(MUX_BIT0+i, GPIO_OUT);
    }
    adc_gpio_init(VOLTAGE_ADC_PIN);
}

void select_range(void)
{
    gpio_put(MUX_BIT0, 0);
    gpio_put(MUX_BIT0+1, 0);
    gpio_put(MUX_BIT0+2, 0);
}