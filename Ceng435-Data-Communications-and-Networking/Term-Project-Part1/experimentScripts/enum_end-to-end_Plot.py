import statistics
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import math

z  = 1.96 # %95 confidence interval
n = 1000

x = [20,40,50]
y = [40.2, 80.3, 100.4]
std = [6.8, 6.9, 7]
std = np.array(std)
error = (z*std) / math.sqrt(n)
#plt.plot(x, y)
#plt.gca().xaxis.set_major_formatter(FormatStrFormatter('%d ms'))
plt.errorbar(x=x[0], y=y[0],xerr=5, yerr=error[0], ls = 'none')
plt.errorbar(x=x[1], y=y[1],xerr=5, yerr=error[1], ls = 'none')
plt.errorbar(x=x[2], y=y[2],xerr=5, yerr=error[2], ls = 'none')
plt.title('Network Emulation Delay vs End-to-End Delay', fontsize=12)
plt.xlabel('Network Emulation Delay', fontsize=9)
plt.ylabel('End-to-End Delay', fontsize=9)
plt.gca().xaxis.set_major_formatter(FormatStrFormatter('%d ms'))
plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%d ms'))
plt.show()