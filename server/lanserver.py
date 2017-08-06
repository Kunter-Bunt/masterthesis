#!/usr/bin/env python

import time
import socket
import _thread as thread
from subprocess import call, Popen, PIPE
import re
import json

def readcmd(proc, num):
	while True: 
		dp = parse_line(proc);
		if dp: s.send(asJSON(dp));
		time.sleep(0.2);

def asJSON(obj):
	j = json.dumps(obj.__dict__);
	j += "___";
	return j.encode();

class DataPoint:
	def __init__(self, time, apmac, stamac, rssi):
		self.time = time;
		self.apmac = apmac;
		self.stamac = stamac;
		self.rssi = rssi;


def parse_line(proc):
	line = proc.stdout.readline().decode("UTF-8");
	regex = re.compile(r"\w+\.py|build|\d+:\d+:\d+");
	#regex = re.compile(r"ProbeReq");
	linelist = re.split("[\s+\n]", line)
	out2 = list(filter(re.compile(r"\w+\.py|build|\d+:\d+:\d+").search, linelist));
	if out2: 
		return DataPoint(1,line,3,4);

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('ideapad', 8080))

processes = [];

for i in range(5):
	command = "ls -a";
	proc = Popen(command.split(), stdout=PIPE);
	processes.append(thread.start_new_thread(readcmd, (proc, i)));
#proc = Popen(["tail", "-f", "/var/log/syslog"], stdout=PIPE);

while True:
	time.sleep(1);



print ("finished");
