import time
import socket
#import _thread as thread
#import re
#import json
#import pexpect
import dill as pickle


from flask import Flask, jsonify, abort, make_response, request
from flask_restful import reqparse

app = Flask(__name__);

class DataPoint(object):
	def __init__(self, time, apmac, stamac, rssi):
		self.time = time;
		self.apmac = apmac;
		self.stamac = stamac;
		self.rssi = rssi;

def loadObject(filename):
    with open(filename, "r") as out:
        return pickle.load(out);

def loadArchive():
    archiveLoad = loadObject("dummydata");
    archive = [];
    for i in range(len(archiveLoad)):
        archive.append({"time": archiveLoad[i].time, "apmac": archiveLoad[i].apmac, "stamac": archiveLoad[i].stamac, "rssi": archiveLoad[i].rssi});
        #print (archive[i]);
    return archive;

def loadDataPoints():
    pass;

datapoints = [
    {"time": 1506419357.1441114, "apmac": "00:a0:57:2b:c4:60", "stamac": "84:ef:18:22:3d:82", "rssi": -23},
    {"time": 1506419359.7743828, "apmac": "00:a0:57:2b:c4:60", "stamac": "74:e2:8c:70:a1:4c", "rssi": -63}
    ];



def filterBy(data, name, value):
    return [datapoint for datapoint in data if datapoint[name] == value];

def filterHigher(data, name, value):
    return [datapoint for datapoint in data if datapoint[name] >= value];

def filterLower(data, name, value):
    return [datapoint for datapoint in data if datapoint[name] <= value];

def applyFilters(data, args):
        remainingDatapoints = data;
        if (args['apmac']):
            remainingDatapoints = filterBy(remainingDatapoints, 'apmac', args['apmac']);
        if (args['stamac']):
            remainingDatapoints = filterBy(remainingDatapoints, 'stamac', args['stamac']);
        if (args['rssi']):
            remainingDatapoints = filterHigher(remainingDatapoints, 'rssi', args['rssi']);
        if (args['time1']):
            remainingDatapoints = filterHigher(remainingDatapoints, 'time', args['time1']);
        if (args['time2']):
            remainingDatapoints = filterLower(remainingDatapoints, 'time', args['time2']);
        if (args['seconds']):
            remainingDatapoints = filterHigher(remainingDatapoints, 'time', time.time()-args['seconds']);
        return remainingDatapoints;

@app.route('/datapoints', methods=['GET'])
def getDatapoints():
    remainingDatapoints = applyFilters(datapoints, parser.parse_args());
    return jsonify({'datapoints': remainingDatapoints});

@app.route('/archive', methods=['GET'])
def getArchive():
    archive = loadArchive();
    remainingDatapoints = applyFilters(archive, parser.parse_args());
    return jsonify({'datapoints': remainingDatapoints});

@app.errorhandler(404)
def notFound(error):
    return make_response(jsonify({'error': 'Not found'}), 404);

def buildParser():
    parser = reqparse.RequestParser();
    parser.add_argument('apmac');
    parser.add_argument('stamac');
    parser.add_argument('time1', type=float, help='time1 could not be converted')
    parser.add_argument('time2', type=float, help='time1 could not be converted')
    parser.add_argument('rssi', type=int, help='rssi could not be converted')
    parser.add_argument('seconds', type=int, help='seconds could not be converted')
    return parser;

if __name__ == '__main__':
    parser = buildParser();
    app.run(debug=True);
