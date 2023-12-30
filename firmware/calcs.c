#include "calcs.h"

float get_voltage_from_code(int code)
{
    return code*LSB;
}

float get_divider_input_voltage(float vout)
{
    float current = vout/DIVIDER_BOTTOM_RESISTOR;
    return current*(DIVIDER_TOP_RESISTOR + DIVIDER_BOTTOM_RESISTOR);
}

float undo_transimpedance_gain(float vout)
{
	return vout/TRANSIMPEDANCE_GAIN;
}
