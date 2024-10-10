#include <stdint.h>
#include <math.h>

#include "calcs.h"

float RMS_signal(uint8_t *signal_array, uint8_t signal_length)
{
    float mean_square  = 0;
    uint8_t i;
    for(i=0;i<signal_length;i++)
        mean_square += signal_array[i]*signal_array[i];
    mean_square /= signal_length;
    float rms = sqrt(mean_square);
    return ((rms*LSB)/BOTTOM_MEASUREMENT_RESISTOR)*(TOP_MEASUREMENT_RESISTOR+BOTTOM_MEASUREMENT_RESISTOR);
}