from math import sqrt, pi

R = [500e3, 50e3, 5e3, 500]
ADC_STEPS = 2**16
REFERANCE = 4.096
SINE_INPUT = REFERANCE/2
FREQUENCY = 100e3
w = 2*pi*FREQUENCY
MAX_VOLTAGE = 1.596
ACCURACY = 0.01
LSB = REFERANCE/ADC_STEPS
MIN_VOLTAGE = LSB/ACCURACY

CURRENT_GAIN = [1e3, 330]

def in_range(voltage): return voltage < MAX_VOLTAGE and voltage > MIN_VOLTAGE

for i, r in enumerate(R):
    min_capacitance = sqrt(SINE_INPUT**2/(w**2*r**2*MAX_VOLTAGE**2) - 1/(w**2*r**2))
    max_capacitance = sqrt(SINE_INPUT**2/(w**2*r**2*MIN_VOLTAGE**2) - 1/(w**2*r**2))
    z = -1j/(w*min_capacitance) + r
    I = abs(SINE_INPUT/z)
    trans_out = list(filter(lambda v: not in_range(v), [I*gain for gain in CURRENT_GAIN]))
    if(len(trans_out) < len(CURRENT_GAIN)): print('current good')
    print('Range Setting: ', r)
    print('Min Capacitance: ', min_capacitance)
    print('Max Capacitance: ', max_capacitance)

for i, r in enumerate(R):
    max_inductance = sqrt(r**2/(((SINE_INPUT**2*w**2)/MAX_VOLTAGE**2) - w**2))
    min_inductance = sqrt(r**2/(((SINE_INPUT**2*w**2)/MIN_VOLTAGE**2) - w**2))
    z = 1j*w*max_inductance
    I = abs(SINE_INPUT/z)
    trans_out = list(filter(lambda v: not in_range(v), [I*gain for gain in CURRENT_GAIN]))
    if(len(trans_out) < len(CURRENT_GAIN)): print('current good')
    print('Range Setting: ', r)
    print('Max Inductance: ', max_inductance)
    print('Min Inductance:  ', min_inductance)
    