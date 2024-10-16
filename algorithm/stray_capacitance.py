from math import pi, sqrt
Vo = 0.2
Vs = 2.5/sqrt(2)
w = 2*pi*100e3
R = 499e3
print(((-1j*Vo)+(1j*Vs))/(-Vo*R*w))
# Calculation results in 25pF of stray capacitance