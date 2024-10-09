import numpy as np
LSB = 3/256
BIAS = 2.5
codes = np.array([int(code) for code in open('test.txt').read().split('\n') if code != '' and code != 'START' and code != 'END'])
nn = [i for i in range(0, len(codes))]
voltages = (codes*LSB*(10e3+6.81e3))/10e3
voltages -= BIAS
RMS_voltage = np.sqrt(np.sum(np.square(voltages))/len(voltages))
RMS_current = RMS_voltage/539
print(RMS_current)