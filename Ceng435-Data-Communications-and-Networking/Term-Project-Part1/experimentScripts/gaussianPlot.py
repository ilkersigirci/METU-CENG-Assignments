# scp  -P 32210  -i ~/.ssh/id_geni_ssh_rsa e2172096@pc2.instageni.colorado.edu:data.json /home/ilker/Network/experimentScripts/

import json
import statistics
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

def myPlot(file):
	with open(file) as inp:
		data = json.load(inp)
		delayArr = data['delays']
	delayArr = np.array(delayArr)
	delayArr = np.sort(delayArr)

	mean = statistics.mean(delayArr)
	std  = statistics.stdev(delayArr)
	#print("{} length: {}, mean: {}, std: {}".format(str(file),len(delayArr), mean, std))
	return delayArr, mean,std

delay20, mean20, std20 = myPlot('delay20.json')
delay40, mean40, std40 = myPlot('delay40.json')
delay50, mean50, std50 = myPlot('delay50.json')

plt.plot(delay20, stats.norm.pdf(delay20,mean20,std20), label = "configured delay 20ms")
plt.plot(delay40, stats.norm.pdf(delay40,mean40,std40), label = "configured delay 40ms")
plt.plot(delay50, stats.norm.pdf(delay50,mean50,std50), label = "configured delay 50ms")
plt.gca().xaxis.set_major_formatter(FormatStrFormatter('%d ms'))
plt.title('Normal Distribution with configured delays', fontsize=12)
plt.xlabel('DELAYS', fontsize=9)
plt.ylabel('PDF', fontsize=9)
plt.legend(loc="upper left")
plt.show()