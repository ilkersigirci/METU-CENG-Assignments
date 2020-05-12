from socket import *
from threading import Thread
import os,stat
import time, random

"""
NOTES
It is only necessary to bind() a server, because the clients need a fixed port number 
to send to. A client needn't bind() at all: an automatic bind() will take place
on the first send()/sendto()/recv()/recvfrom() using a system-assigned local port number.
"""

def s(n,port):
	if   port == 20001: node = "r1" # This is for output purposes
	elif port == 20002: node = "r2"
	elif port == 20003: node = "r3"
	try:
		s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
		s.bind(('', port)) # server binds port to listen packets from it
		print("R1 IS LISTENING THE PORT: {}".format(port))

	except:
		print("R1 CAN NOT BIND THE PORT: ".format(port))

	finally:
		for i in range(n):
			req, peer = s.recvfrom(1000) # getting message and peer
			"""
			if i%100 == 0:
				print("S RECEIVED {} MESSAGES FROM {}".format(i, node))
			#print("request from ",req, " from ", peer)
			"""
			s.sendto(req, peer) # same message packet sent as acknowledge
		s.close()

sServers = []
sServers.append(Thread(target = s, args=(1000,20001)))
sServers.append(Thread(target = s, args=(1000,20002)))
sServers.append(Thread(target = s, args=(1000,20003)))
for sServer in sServers: sServer.start() # different threads to do multiple tasks at the same time
for sServer in sServers: sServer.join()