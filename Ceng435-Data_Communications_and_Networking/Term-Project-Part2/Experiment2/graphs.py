import json
import statistics
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter


""" experiment = [1,2,3,4,5]
loss5_1  = [80,86,78,82,81]
loss15_1 = [252,260,255,246,248]
loss38_1 = [608,610,604,611,602]


loss5_2  = [63,61,64,59,60]
loss15_2 = [134,140,137,135,138]
loss38_2 = [369,371,375,363,372]

plt.plot(experiment, loss5_1, color='red', label = '%5 loss')
plt.plot(experiment, loss15_1, color='orange', label = '%15 loss')
plt.plot(experiment, loss38_1, color='blue', label = '%38 loss')
plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%d s'))
plt.xlabel('Experiment Number')
plt.ylabel('FTT time in seconds')
plt.title('Experiment1 FTT with losses')
plt.legend(loc="upper right")
plt.show() """


""" packetLoss = [5,15,38]
ftt = [80,260,608]
plt.plot(packetLoss, ftt, color='red')
plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%d s'))
plt.xlabel('Packet Loss %')
plt.ylabel('FTT time in seconds')
plt.title('Packet Loss vs FTT')
plt.show() """

""" packetLoss = [5,15,38]
ftt = [63,134,369]
plt.plot(packetLoss, ftt, color='red')
plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%d s'))
plt.xlabel('Packet Loss %')
plt.ylabel('FTT time in seconds')
plt.title('Packet Loss vs FTT')
plt.show() """


def myPlot(loss):
	lossArr = np.array(loss)
	lossArr = np.sort(lossArr)

	mean = statistics.mean(lossArr)
	std  = statistics.stdev(lossArr)
	print("mean: {}, std: {}".format(mean, std))
	return lossArr, mean,std

loss5_1  = [80,86,78,82,81]
loss15_1 = [252,260,255,246,248]
loss38_1 = [608,610,604,611,602]

loss5_2  = [63,61,64,59,60]
loss15_2 = [134,140,137,135,138]
loss38_2 = [369,371,375,363,372]

loss5, mean5, std5 = myPlot(loss5_2)
loss15, mean15, std15 = myPlot(loss15_2)
loss38, mean38, std38 = myPlot(loss38_2)

plt.errorbar(x=5,y=mean5, yerr=std5*1.96,color="red",linestyle="None")
plt.errorbar(x=15,y=mean15, yerr=std15*1.96,color="red",linestyle="None")
plt.errorbar(x=38,y=mean38, yerr=std38*1.96,color="red",linestyle="None")

plt.plot([5,15,38], [mean5,mean15,mean38])
plt.gca().xaxis.set_major_formatter(FormatStrFormatter('%d s'))
plt.xlabel('Packet Loss %')
plt.ylabel('FTT time in seconds')
plt.title('Experiment2 Packet Loss vs FTT')
plt.show()