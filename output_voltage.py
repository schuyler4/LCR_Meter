from math import pi
from cmath import polar

R = 1000 # Ohms
C = 0.1e-6 # Farads
freq = 1000 # Hertz
voltage = 5 # V

def get_output_voltage(R, C, freq, voltage):
    capacitor_impedance = -1j/(2*pi*freq*C)
    impedance = R+capacitor_impedance   
    current = voltage/impedance
    output_voltage, _  = polar(current*capacitor_impedance)
    return output_voltage

for i in range(0, int(1e12)):
    capacitance = i*1e-12

