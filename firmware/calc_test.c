#include <stdio.h>
#include "codes.h"
#include "calcs.h"

int main(void)
{
    int i;
    for(i=0;i < CODE_COUNT; i++)
    {
        int voltage_code = VOLTAGE_CODES[i];
        int current_code = CURRENT_CODES[i];
        float adc_voltage_voltage = get_voltage_from_code(voltage_code);
        float adc_current_voltage = get_voltage_from_code(current_code);
        float capacitor_voltage = get_divider_input_voltage(adc_voltage_voltage);
        float capacitor_current_amplified = get_divider_input_voltage(adc_current_voltage);
		float capacitor_current = undo_transimpedance_gain(capacitor_current_amplified);
        printf("%f\n", capacitor_current);
    }
    return 0;
}
