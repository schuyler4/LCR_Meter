from math import sqrt, pi
from cmath import phase

R = [500e3, 50e3, 5e3, 500]
ADC_STEPS = 2**16
REFERANCE = 4.096
SINE_INPUT = 2.5
FREQUENCY = 100e3
w = 2*pi*FREQUENCY
MAX_VOLTAGE = 1.596
ACCURACY = 0.01
LSB = REFERANCE/ADC_STEPS
MIN_VOLTAGE = LSB/ACCURACY
PHASE_MARGIN = 38 
GBWP = 6e6
CURRENT_GAIN = [2.5e3, 250]

def in_range(voltage): return voltage < MAX_VOLTAGE and voltage > MIN_VOLTAGE

# Resistance 
for r in R:
    Imax = (SINE_INPUT-MIN_VOLTAGE)/r
    Imin = (SINE_INPUT-MAX_VOLTAGE)/r
    Rmin = MIN_VOLTAGE/Imax
    Rmax = MAX_VOLTAGE/Imin
    outMax = [in_range(Imax*gain) for gain in CURRENT_GAIN]
    outMin = [in_range(Imin*gain) for gain in CURRENT_GAIN]
    print(outMax)
    print(outMin)
    print('Max Resistance: ', Rmax)
    print('Min Resistance: ', Rmin)

# Capacitance
for i, r in enumerate(R):
    min_capacitance = sqrt(SINE_INPUT**2/(w**2*r**2*MAX_VOLTAGE**2) - 1/(w**2*r**2))
    max_capacitance = sqrt(SINE_INPUT**2/(w**2*r**2*MIN_VOLTAGE**2) - 1/(w**2*r**2))
    z = -1j/(w*min_capacitance) + r
    I = abs(SINE_INPUT/z)
    trans_out = list(filter(lambda v: not in_range(v), [I*gain for gain in CURRENT_GAIN]))
    voltage_vout = abs(I*(-1j/(w*min_capacitance)))
    print('vout:', voltage_vout)
    print()
    if(len(trans_out) < len(CURRENT_GAIN)): 
        print('current good')
    for gain in CURRENT_GAIN: 
        if in_range(I*gain): 
            print(gain)
            feedback_network = -1j/(2*pi*GBWP*max_capacitance) + r + gain
            Ifeedback = 1/feedback_network
            vout = Ifeedback*(-1j/(2*pi*GBWP*max_capacitance) + r)
            print('Magnitude', abs(vout))
            print('Phase: ', phase(vout)*(180/pi))
            print('Current: ', I)
            print('Range Setting: ', r)
            print('Min Capacitance: ', min_capacitance)
            print('Max Capacitance: ', max_capacitance)

# Inductance
for i, r in enumerate(R):
    max_inductance = sqrt(r**2/(((SINE_INPUT**2*w**2)/MAX_VOLTAGE**2) - w**2))
    min_inductance = sqrt(r**2/(((SINE_INPUT**2*w**2)/MIN_VOLTAGE**2) - w**2))
    z = 1j*w*max_inductance + r
    I = abs(SINE_INPUT/z)
    trans_out = list(filter(lambda v: not in_range(v), [I*gain for gain in CURRENT_GAIN]))
    voltage_vout = abs(1j*w*max_inductance*I) 
    print('vout:', voltage_vout)
    print()
    for gain in CURRENT_GAIN: 
        if in_range(I*gain): 
            print(gain)
            feedback_network = 1j*GBWP*2*pi + r + gain
            Ifeedback = 1/feedback_network
            vout = Ifeedback*(1j*GBWP*2*pi + r)
            print('Magnitude: ', abs(vout))
            print('Phase: ', phase(vout)*(180/pi))
            print('Current: ', I)
            if(len(trans_out) < len(CURRENT_GAIN)): print('current good')
            print('Range Setting: ', r)
            print('Max Inductance: ', max_inductance)
            print('Min Inductance:  ', min_inductance)
    
