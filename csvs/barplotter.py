 # -*- coding: utf-8 -*-

import matplotlib.pyplot as plt 
import numpy as np
import sys

fig = plt.figure();
ax1 = fig.add_subplot(111);

ind = np.arange(4);
width = 0.35

data1 = (88, 88, 32, 1250);
rects1 = ax1.bar(ind, data1, width, color='r');

ax1.set_ylabel('Reichweite in Metern', color='r');
ax1.set_xticks(ind + width / 2);
ax1.set_xticklabels(("Assoziations-\nLokalisierung", "Probe-Request-\nLokalisierung", "BLE-Advertising", "LoRa RSSI \n23 dBm"));

ax2 = ax1.twinx();
data2 = (7.5, 1.8, 0.04, 0.57);
rects2 = ax2.bar(ind + width, data2, width, color='b');

ax2.set_ylabel('Stromverbrauch in mA', color='b');

ax1.plot((0,3.5), (125,125), 'r:');
#ax2.plot((0,4), (0.325,0.325), 'b:');
ax1.text(2.25, 150, ('Vollständige\nAbdeckung').decode('utf8'), ha='center', va='bottom');

def autolabel(ax, rects):
	for rect in rects:
		height = rect.get_height()
		ax.text(rect.get_x() + rect.get_width()/2., 1.05*height, height, ha='center', va='bottom')

autolabel(ax1, rects1);
autolabel(ax2, rects2);

plt.show();
