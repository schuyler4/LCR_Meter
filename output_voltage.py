from math import pi, sqrt

R = 1000 # Ohms
FREQ = 100 # Hertz
VOLTAGE = 5 # V

def get_capacitance(Vr):
    w = 2*pi*FREQ
    a = VOLTAGE**2/((VOLTAGE-Vr)**2*w**2*R**2)
    return sqrt(a - (1/(w**2*R**2)))


print(get_capacitance(2))