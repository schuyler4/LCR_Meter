#include <stdio.h>
#include "codes.h"
#include "calcs.h"

int main(void)
{
    float capacitor_voltages[CODE_COUNT];
    int i;
    float my_component_voltage = component_voltage(VOLTAGE_CODES, CODE_COUNT);
    float my_component_current = component_current(CURRENT_CODES, CODE_COUNT); 
    float my_capacitance = capacitance_uf(my_component_voltage, my_component_current);
    printf("%fV\n", my_component_voltage);
    printf("%fA\n", my_component_current);
    printf("%fuF\n", my_capacitance);
    return 0;
}
