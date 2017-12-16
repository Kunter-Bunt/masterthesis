# -*- coding: utf-8 -*-

import matplotlib
matplotlib.use('Agg');

import matplotlib.pyplot as plt
import numpy as np
import sys



fig = plt.figure(figsize=(8, 5));
ax1 = fig.add_subplot(111);

data1 = (7.5, 1.8, 0.04, 0.3, 0.57);
data2 = (88, 88, 32, 250, 1250);
labels = ("Assoziations-\nLokalisierung", "Probe-Request-\nLokalisierung", "BLE-Advertising", "LoRa RSSI \n5 dBm", "LoRa RSSI \n23 dBm");

ax1.set_xlabel('normalisierter Stromverbrauch in mA');
ax1.set_ylabel('Reichweite in Metern');
ax1.scatter(data1, data2, marker='^', vmin=0, vmax=10, c='seagreen');

for i, label in enumerate(labels):
    ax1.annotate(label, (data1[i],data2[i]));


plt.savefig("scatterplot.png");
