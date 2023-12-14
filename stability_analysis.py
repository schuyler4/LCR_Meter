import time
from math import pi, log10
from cmath import polar
import matplotlib.pyplot as plt
import numpy as np

CLOSED_LOOP_GAIN = 1 # V/V
GBWP = 9e6 # Hz
CUTOFF_FREQUENCY = 10 * 2*pi # RAD / s
OPEN_LOOP_GAIN = 120 # dB
R_OUT = 40 # Ohms
C_LOAD = 10e-9 # Farads

MAGNITUDE_DB = 20

def dB(scale): return MAGNITUDE_DB*log10(scale)
def undo_dB(dB): return 10**(dB/MAGNITUDE_DB)
def rad_to_deg(rad): return rad*(180/pi)

OPEN_LOOP_GAIN_V_PER_V = undo_dB(OPEN_LOOP_GAIN)

def TF(s): return OPEN_LOOP_GAIN_V_PER_V/((1+(s/CUTOFF_FREQUENCY))*(1+s*R_OUT*C_LOAD))
def my_polar(c): return np.array([dB(polar(c)[0]), rad_to_deg(polar(c)[1])])
def w_to_f(w): return w*2*np.pi

def evaluate_TF(TF, min_freq, max_freq):
    ff = np.linspace(min_freq, max_freq, num=1e6)
    transfer_function_mag_phase = np.vectorize(lambda f: np.concatenate((my_polar(TF(f*2*np.pi*1j)), np.array([w_to_f(f)]))), signature='()->(n)')
    return transfer_function_mag_phase(ff)

def find_phase_margin(response):
    zero_db = response[np.argmin(np.abs(response[:,1]))]
    print(zero_db)

def plot_TF(response):
    gain = response[:,0]
    phase = response[:,1]
    frequency = response[:,2]

    _, ax1 = plt.subplots()
    ax2 = ax1.twinx()

    ax1.plot(frequency, gain, color='red', label='gain')
    ax1.set_ylabel('gain (dB)')
    ax1.set_xlabel('frequency (Hz)')
    ax1.set_xscale('log')
    ax2.plot(frequency, phase, label='phase')
    ax2.set_ylabel('Phase(deg)')

    ax1.legend()
    ax2.legend(loc = 0)
    plt.show()

#response =  evaluate_TF(TF, 10, 10e6)



