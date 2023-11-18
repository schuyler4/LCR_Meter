#ifndef CALCS_H
#define CALCS_H

#define PI 3.14159
#define LSB_MULTIPLIER 0.001074
#define SINE_WAVE_SUPPLY_VOLTAGE 5
#define ADC_VOLTAGE_DIVIDER_RATIO 0.2174
#define FREQUENCY 100

float get_capacitor_value_from_ADC(uint16_t code);

#endif