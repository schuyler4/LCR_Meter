from math import pi
Rs = (49.9, 499, 4.9e3, 49e3, 499e3, 4.99e6, 49.9e6) 
Vs = 2.5 
gain = 100
V_ref = 3 # V
LSB = V_ref/2**12
#print(LSB)
threshold = LSB*100
w = 2*pi*10e3

# 
# (Vs - threshold)/Rs = I
# threshold/((Vs - threshold)/Rs) = Rtest
# Rs*threshold/(Vs - threshold) = Rtest
#

for rs in Rs:
    Ztest = rs*threshold/(Vs-threshold) 
    print('Current', Vs/(Ztest+rs))
    print('Resistance:', Ztest)
    print('Capacitance:', 1/(Ztest*w))    
    print('Inductance:', Ztest/w)
