from math import sqrt, pi

R = 1000 # Ohms
FREQ = 100 # Hertz
VOLTAGE = 5 # V

ACCURACY = 0.01
ADC_STEPS = 2896
ADC_VOLTAGE_REFERENCE = 2.5 # V
LSB = ADC_VOLTAGE_REFERENCE/ADC_STEPS # V

MICRO = 1e-6
NANO = 1e-9
PICO = 1e-12

MINIMUM_ADC_VOLTAGE = LSB/ACCURACY
MAXIMUM_ADC_VOLTAGE = ADC_VOLTAGE_REFERENCE - MINIMUM_ADC_VOLTAGE

DIGITS_TO_PRINT = 3

def get_capacitance(Vr, resistor_value):
    # sqrt(1/((VOLTAGE**2/Vr**2) - 1))/(2*pi*FREQ*resistor_value)
    w = 2*pi*FREQ
    return ((VOLTAGE/Vr)**2 - 1)/(w**2*resistor_value**2)


def print_capacitance(capacitance):
    if(capacitance < 1e-3 and capacitance >= 1e-6):
        capacitance_microfarads = capacitance/MICRO
        print(str(round(capacitance_microfarads, DIGITS_TO_PRINT)) + 'uF')
    elif(capacitance < 1e-6 and capacitance >= 1e-9):
        capacitance_nanofarads = capacitance/NANO
        print(str(round(capacitance_nanofarads, DIGITS_TO_PRINT)) + 'nF')
    elif(capacitance < 1e-9):
        capacitance_picofarads = capacitance/PICO
        print(str(round(capacitance_picofarads, DIGITS_TO_PRINT)) + 'pF')


def print_range():
    for i in range(1, 5):
        resistor_value = 10**i*9

        max_first_digit = int(str(get_capacitance(MAXIMUM_ADC_VOLTAGE, resistor_value))[0])
        min_first_digit = int(str(get_capacitance(MINIMUM_ADC_VOLTAGE, resistor_value))[0])

        if(max_first_digit == 1 and min_first_digit == 1):
            print("Resistance: " + str(resistor_value) + " ohms")
            print_capacitance(get_capacitance(MAXIMUM_ADC_VOLTAGE, resistor_value))
            print_capacitance(get_capacitance(MINIMUM_ADC_VOLTAGE, resistor_value))

        if(max_first_digit == 2 and min_first_digit == 1):
            print("Resistance: " + str(resistor_value) + " ohms")
            print_capacitance(get_capacitance(MAXIMUM_ADC_VOLTAGE, resistor_value))
            print_capacitance(get_capacitance(MINIMUM_ADC_VOLTAGE, resistor_value))

        if(max_first_digit == 1 and min_first_digit == 2):
            print("Resistance: " + str(resistor_value) + " ohms")
            print_capacitance(get_capacitance(MAXIMUM_ADC_VOLTAGE, resistor_value))
            print_capacitance(get_capacitance(MINIMUM_ADC_VOLTAGE, resistor_value))
        
        
        if(max_first_digit == 2 and min_first_digit == 2):
            print("Resistance: " + str(resistor_value) + " ohms")
            print_capacitance(get_capacitance(MAXIMUM_ADC_VOLTAGE, resistor_value))
            print_capacitance(get_capacitance(MINIMUM_ADC_VOLTAGE, resistor_value))

print_range()
