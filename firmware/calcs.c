#include <stdio.h>
#include <math.h>
#include "calcs.h"

float voltage_from_code(int code)
{
    return code*LSB;
}

float divider_input_voltage(float vout)
{
    float current = vout/DIVIDER_BOTTOM_RESISTOR;
    return current*(DIVIDER_TOP_RESISTOR + DIVIDER_BOTTOM_RESISTOR);
}

float undo_transimpedance_gain(float vout)
{
	return vout/TRANSIMPEDANCE_GAIN;
}

void remove_DC(float* signal, float* ac_signal, int signal_length)
{
    float mean;
    int i;
    for(i = 0; i < signal_length; i++)
    {
        mean += signal[i];
    }
    mean = mean / signal_length;
    for(i = 0; i < signal_length; i++)
    {
        *(ac_signal + i) = signal[i] - mean;
    }  
}

float rms(float* signal, int signal_length)
{
    float square_sum = 0;
    int i; 	
    for(i = 0; i < signal_length; i++)
    {
        float point = *(signal + i);
        square_sum += point*point;
    }
    float rms = sqrt(square_sum/((float)signal_length)); 
    return rms; 
}

float peak_voltage(float rms_voltage)
{
    return rms_voltage*sqrt(2);
}

float component_voltage(int* voltage_codes, int code_length)
{
    float voltages[code_length];
    float voltages_ac[code_length];
    int i;
    for(i = 0; i < code_length; i++)
    {
        voltages[i] = divider_input_voltage(voltage_from_code(*(voltage_codes + i))); 
        printf("%f\n", voltages[i]);
    }
    remove_DC(voltages, voltages_ac, code_length);
    return peak_voltage(rms(voltages_ac, code_length));
}

float component_current(int* current_codes, int code_length)
{
    float current_voltage[code_length];
    float current_voltage_ac[code_length];
    int i;
    for(i = 0; i < code_length; i++)
    {
        current_voltage[i] = divider_input_voltage(voltage_from_code(*(current_codes + i)));
    }    
    remove_DC(current_voltage, current_voltage_ac, code_length); 
    float currents[code_length];
    for(i = 0; i < code_length; i++)
    {
        currents[i] = undo_transimpedance_gain(current_voltage_ac[i]);   
    }
    return peak_voltage(rms(currents, code_length));
}

float capacitance_uf(float calculated_voltage, float calculated_current)
{
    float reactance = calculated_voltage/calculated_current;
    return 1000000/(2*PI*FREQUENCY*reactance);
}
