from math import pi
cc = (1e-12, 1e-11, 1e-10, 1e-9, 1e-8, 1e-7, 1e-6, 1e-5)
ll = (1e-5, 1e-4, 1e-3, 1e-2)
R = [499, 4.99e3]
V_SINE = 2.5
FREQUENCY = 100e3
LSB = 4.096/2**16
MIN_VOLTAGE = LSB/0.01
MAX_VOLTAGE = 4.096 - MIN_VOLTAGE
w = 2*pi*FREQUENCY
TRANSIMPEDANCE_R = 249 
def in_range(voltage): return voltage < MAX_VOLTAGE and voltage > MIN_VOLTAGE
print('Capacitance')
vv = []
ii = []
for c in cc:
    z = (-1j/(w*c)) + 499
    I = V_SINE/z
    Vout = (-1j/(w*c))*I
    Vout_I = I*TRANSIMPEDANCE_R
    if in_range(abs(Vout_I)) and in_range(abs(Vout)):
        vv.append(abs(Vout))
        ii.append(abs(Vout_I))
        print('C:'+str(c))
        print('I:'+str(abs(I)))
        print('V:'+str(abs(Vout)))
print()
print('Inductance')
for l in ll:
    for r in R: 
        z = (1j*w*l) + r
        I = V_SINE/z
        Vout = (1j*w*l)*I
        Vout_I = I*TRANSIMPEDANCE_R
        if in_range(abs(Vout_I)) and in_range(abs(Vout)):
            print('L:'+str(l))
            print('I:'+str(abs(I)))
            print('V:'+str(abs(Vout)))
V_REF = 4.096
ADC_STEPS = 2**12
LSB = V_REF/ADC_STEPS
qvv = [int(v/LSB) for v in vv] 
qii = [int(i/LSB) for i in ii]
noise_vv = [qv*LSB for qv in qvv]
noise_ii = [qi*LSB for qi in qii] 
noise_zz = [noise_vv[i]/(noise_ii[i]/TRANSIMPEDANCE_R) for i in range(0, len(noise_vv))]
noise_cc = [1/(w*z) for z in noise_zz]
print()
print('Capacitance with Quantization Noise')
for c in noise_cc:
    print(c)
