#!/usr/bin/env python

import socket
import time
import _thread as thread
from subprocess import call, Popen, PIPE
import re
import json

def asJSON(obj):
	return json.dumps(obj.__dict__);

def dataPointFromJSON(obj):
	return DataPoint(obj["time"], obj["apmac"], obj["stamac"], obj["rssi"]);

class DataPoint:
	def __init__(self, time, apmac, stamac, rssi):
		self.time = time;
		self.apmac = apmac;
		self.stamac = stamac;
		self.rssi = rssi;

def on_new_client (conn, addr):
		data = "";
		while True:
			data += conn.recv(64).decode("UTF-8");	
			if data: 
				try: 
					cur, data = data.split("___",1);
					print ("received data:", cur, "from:", addr);
					json.loads(cur, object_hook=dataPointFromJSON);
				except ValueError: pass;
			time.sleep(1);


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);

s.bind(('ideapad', 8080));
s.listen(5);

try:
	while True:
		conn, addr = s.accept()
		thread.start_new_thread(on_new_client, (conn, addr));
except KeyboardInterrupt: print ("Exiting...");
