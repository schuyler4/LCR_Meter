#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "main.h"

#define TIMER_INTERVAL_US 2.5

int16_t i = 0;
uint8_t capture_complete = 0;
uint8_t current_sample_buffer[ADC_SAMPLE_COUNT];  
uint8_t voltage_sample_buffer[ADC_SAMPLE_COUNT];

int main(void)
{
    stdio_init_all();
    setup_GPIO();
    adc_init();
    select_range();
    adc_fifo_setup(true, true, 1, false, true);
    adc_set_clkdiv(0);

    uint dma_chan = dma_claim_unused_channel(true);
    dma_channel_config cfg = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    channel_config_set_dreq(&cfg, DREQ_ADC);

    dma_channel_configure(dma_chan, &cfg, current_sample_buffer, &adc_hw->fifo, ADC_SAMPLE_COUNT, true);
    adc_select_input(CURRENT_ADC_CHANNEL);
    adc_run(true);
    dma_channel_wait_for_finish_blocking(dma_chan);
    adc_run(false);
    adc_fifo_drain();

    dma_channel_configure(dma_chan, &cfg, voltage_sample_buffer, &adc_hw->fifo, ADC_SAMPLE_COUNT, true);
    adc_select_input(VOLTAGE_ADC_CHANNEL);
    adc_run(true);
    dma_channel_wait_for_finish_blocking(dma_chan);
    adc_run(false);
    adc_fifo_drain();

    while(1)
    {
        printf("START\n");
        uint16_t i;
        for(i = 0; i < ADC_SAMPLE_COUNT; i++)
        {
            printf("%d\n", sample_buffer[i]);
        }
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
    adc_gpio_init(CURRENT_ADC_PIN);
}

void select_range(void)
{
    gpio_put(MUX_BIT0, 0);
    gpio_put(MUX_BIT0+1, 0);
    gpio_put(MUX_BIT0+2, 0);
}
