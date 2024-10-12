#ifndef CALCS_H
#define CALCS_H

#define TOP_MEASUREMENT_RESISTOR 6810
#define BOTTOM_MEASUREMENT_RESISTOR 10000
#define ADC_STEPS 256
#define ADC_VOLTAGE_REFERENCE 2.987
#define LSB (ADC_VOLTAGE_REFERENCE/ADC_STEPS)

float RMS_signal(uint8_t *signal_array, uint16_t signal_length);
float get_max_voltage(uint8_t *signal_array, uint8_t signal_length);
float get_min_voltage(uint8_t *signal_array, uint8_t signal_length);

#endif