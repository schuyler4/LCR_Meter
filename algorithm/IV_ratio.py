Rs = 499e3 
Vs = 2.5 
gain = 100
V_ref = 3 # V
LSB = V_ref/2**12
#print(LSB)
threshold = LSB*200

# I = Vs/(Rs + Ztest)
# V = Vs*Ztest/(Rs + Ztest)

# Vs*gain/(Rs + Ztest) > threshold  
# 1/(Rs + Ztest) > threshold/(Vs*gain)
# Ztest > ((Vs*gain)/threshold) - Rs
# Resistor
# Rtest > ((Vs*gain)/threshold) - Rs
#
# Vs*Rs/(Rs + Rtest) > threshold
# 1/(Rs + Rtest) > threshold/(Vs*Rs)
# Rs + Rtest > (Vs*Rs)/threshold
# 1/Vs + Rtest/(Vs*Rs) > 1/threshold
# 
#
#

print((Vs*gain/threshold) - Rs)