#!/usr/bin/env python

import socket
import time
import _thread as thread
from subprocess import call, Popen, PIPE
import re

def on_new_client (conn, addr):
		while True:
			data = conn.recv(64);
			if data: print ("received data:", data, "from:", addr);
			time.sleep(1);

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);

s.bind(('ideapad', 8080));
s.listen(5);



try:
	while True:
		conn, addr = s.accept()
		thread.start_new_thread(on_new_client, (conn, addr));
except KeyboardInterrupt:
	print ("Exiting...");

