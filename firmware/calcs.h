#ifndef CALCS_H
#define CALCS_H

#define ADC_REFERENCE 4.096
#define ADC_STEPS 65540
#define LSB (ADC_REFERENCE/ADC_STEPS)
#define DIVIDER_TOP_RESISTOR 2210
#define DIVIDER_BOTTOM_RESISTOR 10000
#define TRANSIMPEDANCE_GAIN 250
#define FREQUENCY 100000
#define PI 3.14159
 
float voltage_from_code(int code);
float divider_input_voltage(float vout);
float undo_transimpedance_gain(float vout);
void remove_DC(float* signal, float* ac_signal, int signal_length);
float rms(float* signal, int signal_length);
float component_voltage(int* voltage_codes, int code_length);
float component_current(int* current_codes, int code_length);
float peak_voltage(float rms_voltage);
float capacitance_uf(float component_voltage, float component_current);

#endif
