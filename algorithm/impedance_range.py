cc = (1e-12, 1e-11, 1e-10, 1e-9, 1e-8, 1e-7, 1e-6, 1e-5)
R = 499
V_SINE = 2.5
FREQUENCY = 100e3
for c in cc:
    z = (-1j/(w*c)) + R
    I = V_SINE/z
    Vout = (-1j/(w*c))*I
