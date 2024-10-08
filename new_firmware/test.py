import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np
codes = [int(code) for code in open('test.txt').read().split('\n') if code != '' and code != 'START' and code != 'END']
nn = [i for i in range(0, len(codes))]
guess_offset = np.mean(codes) 
guess_amplitude = 3*np.std(codes)/(2**0.5)
guess_freq = 1
guess_phase = 0
p0 = [guess_freq, guess_amplitude, guess_phase, guess_offset]

def my_sin(x, freq, amplitude, phase, offset): return np.sin(x*freq+phase)*amplitude + offset

plt.plot(nn, codes)
plt.show()