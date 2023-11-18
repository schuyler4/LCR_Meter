static float get_ADC_voltage(uint16_t code)
{
    return LSB_MULTIPLIER*code;
}

static float divided_voltage(float divider_input)
{
    return ADC_VOLTAGE_DIVIDER_RATIO*divider_input;
}

static float get_capacitor_value(float divider_voltage)
{
    float Xc = divider_voltage/(SINE_WAVE_SUPPLY_VOLTAGE-divider_voltage);
    return 1/(2*PI*Xc*FREQUENCY);
}

float get_capacitor_value_from_ADC(uint16_t code)
{
    return get_capacitor_value(divided_voltage(get_ADC_voltage(code)));
}