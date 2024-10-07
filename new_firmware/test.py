import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
codes = [int(code) for code in open('test.txt').read().split('\n') if code != '' and code != 'START' and code != 'END']
nn = [i for i in range(0, len(codes))]
plt.plot(nn, codes)
plt.show()