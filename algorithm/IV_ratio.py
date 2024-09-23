from math import pi
Rs = (49.9, 499, 4.9e3, 49e3, 499e3, 4.99e6, 49.9e6) 
Vs = 2.5 
gain = 100
V_ref = 3 # V
LSB = V_ref/2**12
threshold = LSB*100
w = 2*pi*200e3

# 
# (Vs - threshold)/Rs = I
# threshold/((Vs - threshold)/Rs) = Rtest
# Rs*threshold/(Vs - threshold) = Rtest
#
# threshold/Rs = I
# (Vs - threshold)/(threshold/Rs) = Rtest
# Rs(Vs-thrshold)/threshold = Rtest
#


for rs in Rs:
    print(rs)
    min_Ztest = rs*threshold/(Vs-threshold) 
    max_Ztest = rs*(Vs-threshold)/threshold
    print('Max Current', Vs/(min_Ztest+rs))
    print('Min Current', Vs/(max_Ztest+rs))
    print('Min Resistance:', min_Ztest)
    print('Max Resistance:', max_Ztest)
    print('Max Capacitance:', 1/(min_Ztest*w))    
    print('Min Capacitance:', 1/(max_Ztest*w))    
    print('Min Inductance:', min_Ztest/w)
    print('Max Inductance:', max_Ztest/w)
    print()
