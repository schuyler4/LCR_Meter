from math import sqrt, pi
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.signal import resample, remez

SAMPLE_RATE = 10e6
SAMPLE_PERIOD = 1/SAMPLE_RATE

# Done without built in functions because that is what will be needed in C.
class ValueFinder:
    R_TOP = 2.21e3
    R_BOTTOM = 10e3
    TRANSIMPEDANCE_GAIN = 250
    SIGNAL_FREQUENCY = 100e3
    HIGH_PASS_CUTOFF = 50e3 
    HIGH_PASS_LENGTH = 10
    HIGH_PASS_TAU = 1/(2*pi*HIGH_PASS_CUTOFF)
    
    def __init__(self, voltage_samples, current_samples, times):
        self.voltage_samples = voltage_samples
        self.current_samples = current_samples
        self.times = times
    
    def input_voltage(self, output_voltage):
        I = output_voltage/(self.R_TOP + self.R_BOTTOM)
        return I*self.R_BOTTOM
    
    def capacitance(self, reactance):
        return 1/(2*pi*reactance*self.SIGNAL_FREQUENCY)
    
    def mean(self, signal):
        mean = 0
        for point in signal:
            mean += point
        mean = mean/len(signal)
        return mean
    
    def DC_Blocker(self, signal):
        signal_mean = self.mean(signal)
        ac_signal = []
        for point in signal:
            ac_signal.append(point - signal_mean)
        return ac_signal
    
    def RMS(self, sampled_amplitude):
        sum_square = 0
        for sample in sampled_amplitude:
            sum_square += sample**2
        return sqrt(sum_square/len(sampled_amplitude)) 

    def measured_capacitance(self):
        UNDO_GAIN = 1/self.TRANSIMPEDANCE_GAIN
        mag_voltage = self.input_voltage(self.RMS(self.DC_Blocker(self.voltage_samples))*sqrt(2))
        mag_current = self.input_voltage(self.RMS(self.DC_Blocker(self.current_samples))*sqrt(2))*UNDO_GAIN
        return self.capacitance(mag_voltage/mag_current)
       

voltage_data = np.array(pd.read_csv('voltage.txt', sep = '\t', header=None))
current_data = np.array(pd.read_csv('current.txt', sep = '\t', header=None))

voltage_data_time = voltage_data[:,0]
voltage_data_voltage = voltage_data[:,1]

current_data_time = current_data[:,0]
current_data_voltage = current_data[:,1]

time_length = voltage_data_time[voltage_data_time.size - 1] - voltage_data_time[0]
ADC_sample_count = (int)(time_length/SAMPLE_PERIOD)

ADC_voltage_samples = resample(voltage_data_voltage, ADC_sample_count)
ADC_current_samples = resample(current_data_voltage, ADC_sample_count)
times = np.linspace(0, time_length, num=ADC_sample_count)

capacitance_value_finder = ValueFinder(ADC_voltage_samples, ADC_current_samples, times)
ac_voltage = capacitance_value_finder.DC_Blocker(ADC_voltage_samples)
ac_current = capacitance_value_finder.DC_Blocker(ADC_current_samples)

print(capacitance_value_finder.measured_capacitance())
print(capacitance_value_finder.mean(ADC_voltage_samples))
print(capacitance_value_finder.mean(ADC_current_samples))

plt.plot(times, ac_current)
plt.plot(times, ac_voltage)
plt.show()

plt.plot(voltage_data_time, voltage_data_voltage)
plt.show()

plt.plot(current_data_time, current_data_voltage)
plt.show()
