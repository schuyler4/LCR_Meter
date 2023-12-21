from math import sqrt, pi
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.signal import resample 

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
    
    def __init__(self, voltage_samples, current_samples, peak_detect_mode=False):
        self.voltage_samples = voltage_samples
        self.current_samples = current_samples
        self.peak_detect_mode = peak_detect_mode
    
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

    def RMS_peak(self, sampled_amplitude):
        return self.RMS(sampled_amplitude)*sqrt(2)

    def peak_detector(self, signal):
        max_point = 0
        for point in signal:
            if(point > max_point):
                max_point = point
        return max_point

    def measured_capacitance(self):
        UNDO_GAIN = 1/self.TRANSIMPEDANCE_GAIN
        if(not self.peak_detect_mode):
            mag_voltage = self.input_voltage(self.RMS_peak(self.DC_Blocker(self.voltage_samples)))
            mag_current = self.input_voltage(self.RMS_peak(self.DC_Blocker(self.current_samples)))*UNDO_GAIN
            return self.capacitance(mag_voltage/mag_current)
        else:
            mag_voltage = self.input_voltage(self.peak_detector(self.DC_Blocker(self.voltage_samples)))
            mag_current = self.input_voltage(self.peak_detector(self.DC_Blocker(self.current_samples))*UNDO_GAIN)
            return self.capacitance(mag_voltage/mag_current)
       
def is_evenly_spaced(data):
    last_point = 0
    space = None
    for point in data:
       new_space = point - last_point
       if(space is not None and not np.isclose(new_space, space)): return False
       space = new_space
    return True

voltage_data = np.array(pd.read_csv('voltage.txt', sep = '\t', header=None))
current_data = np.array(pd.read_csv('current.txt', sep = '\t', header=None))

voltage_data_time = voltage_data[:,0]
voltage_data_voltage = voltage_data[:,1]

current_data_time = current_data[:,0]
current_data_voltage = current_data[:,1]

print(is_evenly_spaced(voltage_data_time))
print(is_evenly_spaced(current_data_time))

time_length = voltage_data_time[voltage_data_time.size - 1] - voltage_data_time[0]
ADC_sample_count = (int)(time_length/SAMPLE_PERIOD)

ADC_voltage_samples, _ = resample(voltage_data_voltage, ADC_sample_count, t=voltage_data_time)
ADC_current_samples, _ = resample(current_data_voltage, ADC_sample_count, t=current_data_time)
times = np.linspace(0, time_length, num=ADC_sample_count)

value_finder_resampled = ValueFinder(ADC_voltage_samples, ADC_current_samples)
ac_voltage = value_finder_resampled.DC_Blocker(ADC_voltage_samples)
ac_current = value_finder_resampled.DC_Blocker(ADC_current_samples)

print(value_finder_resampled.measured_capacitance())
print(value_finder_resampled.mean(ADC_voltage_samples))
print(value_finder_resampled.mean(ADC_current_samples))

value_finder_original_data = ValueFinder(voltage_data_voltage, current_data_voltage, peak_detect_mode=True)
print(value_finder_original_data.measured_capacitance())

plt.plot(times, ac_current)
plt.plot(times, ac_voltage)
plt.show()

plt.title('Voltage Resampling')
plt.plot(voltage_data_time, voltage_data_voltage)
plt.scatter(times, ADC_voltage_samples, s=2, color='red')
plt.show()

plt.title('Current Resampling')
plt.plot(current_data_time, current_data_voltage)
plt.scatter(times, ADC_current_samples, s=2, color='red')
plt.show()
