import matplotlib.pyplot as plt 
import numpy as np
import sys

data = np.genfromtxt(sys.argv[1], delimiter=',', names=['x', 'y']);
fig = plt.figure()
ax1 = fig.add_subplot(111)

ax1.set_xlabel('Zeit in ms')
ax1.set_ylabel('Stromverbrauch in mA')
ax1.plot(data['x'], data['y'], color='r', marker='.');
ax1.fill_between(data['x'], data['y'], 0, facecolor='red', alpha=0.4, interpolate=True)

#plt.plotfile('probeReq3ch.csv', delimiter=',', cols=(0, 1), names=('Zeit in ms', 'Stromverbrauch in mA'), marker='.');
plt.show();
