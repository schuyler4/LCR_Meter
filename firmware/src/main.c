#include <avr/io.h>

#include "main.h"
#include "ADC.h"
#include "UART.h"
#include "running_average.h"
#include "calcs.h"

static volatile unsigned int adc_value;
static volatile unsigned uint8_t adc_complete_flag = 0;

static Running_Average_Filter component_voltage_filter;

int main(void)
{
    setup_ADC();
    setup_UART();

    component_voltage_filter.length = COMPONENT_VOLTAGE_FILTER_LENGTH;

    // The first one. 
    start_ADC_conversion();

    while(1)
    {
        if(adc_complete_flag)
        {
            adc_complete(adc_value);
        }
    }

    // The program should never return.
    return 1;
}

void adc_complete(int value)
{
    adc_complete_flag = 0;
    component_voltage_filter.sample = value;
    uint16_t component_voltage_filter_average_value = running_average_filter_sample(&component_voltage_filter);
    float measured_capacitance = get_capacitor_value_from_ADC(component_voltage_filter_average_value);
    uint16_t measured_capacitance_integer = ((uint16_t)(measured_capacitance*1000))
    UART_transmit_uint16_t(measured_capacitance_integer);
}

ISR(ADC_vect)
{
    adc_value = ADC;
    adc_complete_flag = 1;
}