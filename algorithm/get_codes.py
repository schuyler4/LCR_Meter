import numpy as np
import pandas as pd
from scipy.signal import resample

R_TOP = 2.21e3
R_BOTTOM = 10e3

SAMPLE_RATE = 500e3
SAMPLE_PERIOD = 1/SAMPLE_RATE
ADC_REFERANCE = 4.096
ADC_RESOLUTION = 16 
LSB = ADC_REFERANCE/(2**ADC_RESOLUTION)

def voltage_code(voltages):
    return [int(voltage/LSB) for voltage in voltages]   

voltage_data = np.array(pd.read_csv('voltage.txt', sep='\t', header=None))
current_data = np.array(pd.read_csv('current.txt', sep='\t', header=None))

voltage_data_time = voltage_data[:,0]
voltage_data_voltage = voltage_data[:,1]

current_data_time = current_data[:,0]
current_data_voltage = current_data[:,1]

time_length = voltage_data_time[voltage_data_time.size - 1] - voltage_data_time[0]
ADC_sample_count = (int)(time_length/SAMPLE_PERIOD)

ADC_voltage_samples, _ = resample(voltage_data_voltage, ADC_sample_count, t=voltage_data_time)
ADC_current_samples, _ = resample(current_data_voltage, ADC_sample_count, t=current_data_time)

print(voltage_code(ADC_voltage_samples))
print(voltage_code(ADC_current_samples))
