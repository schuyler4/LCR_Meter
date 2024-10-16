#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "main.h"
#include "calcs.h"

#define TIMER_INTERVAL_US 2.5

int16_t i = 0;
uint8_t capture_complete = 0;
uint8_t current_sample_buffer[ADC_SAMPLE_COUNT];  
uint8_t voltage_sample_buffer[ADC_SAMPLE_COUNT];
uint dma_chan;
dma_channel_config cfg;

int main(void)
{
    stdio_init_all();
    setup_GPIO();
    adc_init();
    adc_fifo_setup(true, true, 1, false, true);
    adc_set_clkdiv(0);

    dma_chan = dma_claim_unused_channel(true);
    cfg = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    channel_config_set_dreq(&cfg, DREQ_ADC);

    while(1)
    { 
        float reading = take_reading();
        printf("%f\n", reading);
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

void select_range(uint8_t range)
{
    gpio_put(MUX_BIT0, (range & 0x01) != 0);
    gpio_put(MUX_BIT0+1, (range & 0x02) != 0);
    gpio_put(MUX_BIT0+2, (range & 0x04) != 0);
}

float take_reading(void)
{
    float average = 0;
    uint8_t range = 0;
    uint8_t range_index = 0;
    uint8_t i;
    for(i=0;i<100;i++)
    {
//capture_start:
        select_range(3);

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

        float rms_voltage_signal = RMS_signal(voltage_sample_buffer, ADC_SAMPLE_COUNT);
        float rms_current_signal = RMS_signal(current_sample_buffer, ADC_SAMPLE_COUNT);
        float rms_current = rms_current_signal/(RANGE_RESISTORS[range_index] + 73);
        printf("%f\n", rms_voltage_signal);
        printf("%d\n", range);

        float voltage_high = rms_voltage_signal > 0.4;
        float voltage_low =  rms_voltage_signal < 1.767*0.05;

/*        if(voltage_high && range < 5)
        {
            range += 1;
            range_index+=1;
            goto capture_start;
        }

        if(voltage_low && range > 0)
        {
            range -= 1; 
            range_index -= 1;
            goto capture_start;
        }*/
        average += rms_voltage_signal/rms_current;
    }
    printf("%d\n", range);
    return average/100;
}