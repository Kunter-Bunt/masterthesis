#!/usr/bin/env python

import time
import socket
import _thread as thread
import re
import json
import pexpect

verbose = True;
logging = True;

#the thread function for every ap
def readcmd(proc):
	#get mac address of ap
	proc.send('sysinfo\r\n');
	apmac = parse_sysinfo(proc);
	apmac = apmac[0:2] + ":" + apmac[2:4] + ":" + apmac[4:6] + ":" + apmac[6:8] + ":" + apmac[8:10] + ":" + apmac[10:];

	#enable logging
	proc.send('trace + wlan-data @ ProbeReq\r\n');

	#start parsing the log
	while True:
		dp = parse_line(proc, apmac);
		if dp and logging: print(asJSON(dp).decode("UTF-8"));
		if dp: s.send(asJSON(dp));
		time.sleep(0.05);

#___ is separator
def asJSON(obj):
	j = json.dumps(obj.__dict__);
	j += "___";
	return j.encode();

class DataPoint(object):
	def __init__(self, time, apmac, stamac, rssi):
		self.time = time;
		self.apmac = apmac;
		self.stamac = stamac;
		self.rssi = rssi;

#reads a line from stdout of proc
def decline(proc):
	return proc.readline().decode("UTF-8");

#find mac in sysinfo
def parse_sysinfo(proc):
	apmac = "";
	found = False;
	while not found:
		line = decline(proc);
		if verbose: print (line);
		if re.match((r"MAC-ADDRESS:."), line):
			lines = re.split(r"\s", line);
			apmac = list(filter(re.compile(r"[a-z0-9]+").search, lines));
			found = True;
	if apmac: return apmac[0];

#find wlan-data as package start, read out sender mac and rssi
def parse_line(proc, apmac):
	#packet start
	line = decline(proc);
	if verbose: print (line);
	if re.match((r".WLAN-DATA."), line):

		#only incoming packets
		line = decline(proc);
		if verbose: print (line);
		if re.match((r"Received."), line):
			stamac = list(re.findall(r"\w+:\w+:\w+:\w+:\w+:\w+", line));
			if stamac:
				stamac = stamac[0];

				#iterate to "-->Signal: " to catch rssi
				rssi = "";
				found = False;
				while not found:
					line = decline(proc);
					if verbose: print (line);
					if re.match((r"-->Signal:."), line):
						rssi = list(re.findall(r"-\d+", line));
						found = True;
				if rssi:
					return DataPoint(time.time(),apmac,stamac,int(rssi[0]));
				else: print ("Corrupted RSSI");
			else: print ("Corrupted Station MAC");

#server connection
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('ideapad', 8080))

#start the sessions
for i in range(1):
	#child = pexpect.spawn('cat saveap/full');
	child = pexpect.spawn('ssh -t root@192.168.200.254');
	child.expect('Password:');
	child.sendline('key4Lancom!');
	thread.start_new_thread(readcmd, (child,));

#loop while sessions are open
while True: time.sleep(1);
