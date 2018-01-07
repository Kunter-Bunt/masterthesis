import time
import random
import dill as pickle

filepath = "dummyarchive"
amount = 10000

class DataPoint(object):
	def __init__(self, time, apmac, stamac, rssi):
		self.time = time;
		self.apmac = apmac;
		self.stamac = stamac;
		self.rssi = rssi;

apmacs = ["00:a0:57:2b:c4:60", "00:a0:57:2b:c4:61", "00:a0:57:2b:c4:62", "00:a0:57:2b:c4:63", "00:a0:57:2b:c4:64"];
stamacs = ["74:e2:8c:70:a1:4c", "84:ef:18:22:3d:82", "ec:10:7b:28:3a:bd", "de:ef:09:dc:ea:64", "0c:47:c9:54:cd:3b"];
datapoints = [];
start = time.time()
def saveObject(obj, filename):
    with open(filename, "w") as out:
        pickle.dump(obj, out, -1);

def loadObject(filename):
    with open(filename, "r") as out:
        return pickle.load(out);

for i in range(amount):
	datapoints.append(DataPoint(time.time()-random.random()*500, random.choice(apmacs), random.choice(stamacs), random.randint(-100, 0)));

	print (datapoints[i]);

saveObject(datapoints, filepath);
savetime = time.time()-start;
start = time.time();
datapoints2 = loadObject(filepath);
loadtime = time.time()-start;

for i in range(100):
    print (datapoints2[i].time, datapoints2[i].apmac, datapoints2[i].stamac, datapoints2[i].rssi);

print (savetime, loadtime);
