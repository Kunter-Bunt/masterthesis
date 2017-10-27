import matplotlib.pyplot as plt 
import numpy as np
import sys

#data = np.genfromtxt(sys.argv[1], delimiter=',', names=['x', 'y', 'z']);
#data = np.genfromtxt(sys.argv[1], delimiter=',', names=['x', 'y', 'z', 'v']);
#data = np.genfromtxt(sys.argv[1], delimiter=',', names=['x', 'y']);
data = np.genfromtxt(sys.argv[1], delimiter=',', names=['x', 'y', 'z', 'v', 'w', 'u']);
fig = plt.figure()
ax1 = fig.add_subplot(111)

ax1.set_xlabel('Zeit in ms')
ax1.set_ylabel('Stromverbrauch in mA')

ax1.fill_between(data['x'], data['y'], 0, facecolor='r', alpha=0.4, interpolate=True)
#ax1.fill_between(data['x'], data['u'], 0, facecolor='m', alpha=0.4, interpolate=True)

ax1.plot(data['x'], data['y'], color='r', marker='');
ax1.plot(data['x'], data['z'], color='g', marker='');
ax1.plot(data['x'], data['v'], color='b', marker='');
ax1.plot(data['x'], data['w'], color='k', marker='');
ax1.plot(data['x'], data['u'], color='m', marker='');

#plt.plotfile('probeReq3ch.csv', delimiter=',', cols=(0, 1), names=('Zeit in ms', 'Stromverbrauch in mA'), marker='.');
plt.show();
