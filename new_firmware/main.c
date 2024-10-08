#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#include "main.h"

#define TIMER_INTERVAL_US 2.5

int16_t i = 0;
uint8_t capture_complete = 0;
uint16_t sample_buffer[ADC_SAMPLE_COUNT];  

int main(void)
{
    stdio_init_all();
    setup_GPIO();
    adc_init();
    select_range();
    adc_fifo_setup(true, false, 0, false, false);
    //adc_run(true);

    //repeating_timer_t sampling_timer;
    //if(!add_repeating_timer_us(2.5, sample_timer_callback, NULL, &sampling_timer))
    //{
    //    printf("ERROR CREATING TIMER");
    //    return 1;
    //}

    while(1)
    {
        printf("MADE IT TO THE LOOP");
        if(capture_complete)
        {
            adc_fifo_drain();
            adc_run(false);
            //cancel_repeating_timer(&sampling_timer);
            printf("START\n");
            for(i=0;i<ADC_SAMPLE_COUNT;i++)
                printf("%d\n", sample_buffer[i]);
            printf("END\n");
        }
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

bool sample_timer_callback(repeating_timer_t *rt)
{
    printf("SAMPLING");
    if(i < ADC_SAMPLE_COUNT)
    {
        sample_buffer[i] = adc_fifo_get_blocking();  
        i++;
        return true;
    }
    else
    {
        capture_complete = 1;
        return false;
    }
}