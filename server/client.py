#!/usr/bin/env python

import socket
import time

BUFFER_SIZE = 1024
MESSAGE = "Hello, World!"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('ideapad', 8080))

while 1:
	s.send(MESSAGE)
	time.sleep(1);

s.close()
