#ifndef CALCS_H
#define CALCS_H

#define ADC_REFERENCE 4.096
#define ADC_STEPS 65540
#define LSB (ADC_REFERENCE/ADC_STEPS)
#define DIVIDER_TOP_RESISTOR 2210
#define DIVIDER_BOTTOM_RESISTOR 10000
#define TRANSIMPEDANCE_GAIN 250
 
float get_voltage_from_code(int code);
float get_divider_input_voltage(float vout);
float undo_transimpedance_gain(float vout);

#endif
