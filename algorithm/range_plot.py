import matplotlib.pyplot as plt
from math import pi

import numpy as np

REFERANCE = 4.096
ADC_STEPS = 2**16
FREQUENCY = 100e3
SINE_INPUT = 2.5
ACCURACY = 0.01
LSB = REFERANCE/ADC_STEPS
MAX_VOLTAGE = 1.596
MIN_VOLTAGE = LSB/ACCURACY
R = 500
w = 2*pi*FREQUENCY

def in_range(voltage): return voltage < MAX_VOLTAGE and voltage > MIN_VOLTAGE

def filter_stuff(vv, ii, cc):
    filtered_vv = []
    filtered_cc = []
    for i, v in enumerate(vv):
        if in_range(v) and in_range(ii[i]):
            filtered_vv.append(v)        
            filtered_cc.append(cc[i])
    return filtered_vv, filtered_cc

index = [i for i in range(1, 1000000)]
capacitance = np.array([1e-12*i for i in index])
z_comp = 1j/(2*pi*w*capacitance)
Z = R + z_comp
I = SINE_INPUT/Z 
current = [i*250 for i in I] 
vout = abs(I*z_comp)
filtered_voltage, filtered_capacitance = filter_stuff(vout, current, capacitance) 
plt.plot(filtered_capacitance, filtered_voltage)
plt.show()
