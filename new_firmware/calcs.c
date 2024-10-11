#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "calcs.h"

float RMS_signal(uint8_t *signal_array, uint8_t signal_length)
{
    float mean_square  = 0;
    uint8_t i;
    for(i=0;i<signal_length;i++)
    {
        float voltage = (((float)signal_array[i]*LSB)/BOTTOM_MEASUREMENT_RESISTOR)*(TOP_MEASUREMENT_RESISTOR+BOTTOM_MEASUREMENT_RESISTOR)-2.5;
        mean_square += voltage*voltage;
    }
    mean_square /= signal_length;
    return sqrt(mean_square);
}

float get_max_voltage(uint8_t *signal_array, uint8_t signal_length)
{
    float max_voltage = 0;
    uint8_t i;
    for(i=0;i<signal_length;i++) 
    {
        float voltage = (float)signal_array[i]*LSB;
        if(voltage > max_voltage)
            max_voltage = voltage;
    }
    return max_voltage;
}

float get_min_voltage(uint8_t *signal_array, uint8_t signal_length)
{
    float min_voltage = ADC_VOLTAGE_REFERENCE;
    uint8_t i;
    for(i=0;i<signal_length;i++) 
    {
        float voltage = (float)signal_array[i]*LSB;
        if(voltage < min_voltage)
            min_voltage = voltage;
    }
    return min_voltage;
}