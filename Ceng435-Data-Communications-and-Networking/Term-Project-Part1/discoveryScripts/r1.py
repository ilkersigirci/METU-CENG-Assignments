from socket import *
from threading import Thread
import os,stat
import time, random
import statistics

def r1(n,ip,port):
	if   port == 20001: node = "s" # This is for output purposes
	elif port == 20011: node = "d"
	elif port == 20005: node = "r2"
	print("R1 WILL SEND MESSAGE TO: {} OVER {}".format(node, ip, port))
	c = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket 
	elapsed = [] # this list will hold all rtt values
	for i in range(n):
		"""
		if i%100 == 0:
			print("R1 SENT {} MESSAGES TO {}".format(i, node))
		"""
		start = time.time() # timestamp before sending packet
		c.sendto(b'message from r1', (ip, port)) # to send packet, destination ip and port must be specified
		result, peer = c.recvfrom(1000) # acknowledge is expected from server side
		done = time.time() # timestamp after getting acknowledge
		difference = done - start # rtt calculation
		elapsed.append(difference) 
		#print("Result:" , result, "Peer:", peer)

	elapsedMean = statistics.mean(elapsed) # average of all rtts are calculated
	elapsedMean *= 1000 # Convert seconds to milliseconds
	print("Average delay between r1 and {} is : {} ms".format(node, elapsedMean))

r1Clients = []
r1Clients.append( Thread(target = r1, args=(1000,'10.10.1.1',20001)) )
r1Clients.append( Thread(target = r1, args=(1000,'10.10.4.2',20011)) )
r1Clients.append( Thread(target = r1, args=(1000,'10.10.8.2',20005)) )
for r1Client in r1Clients: r1Client.start() # different threads to do multiple tasks at the same time
for r1Client in r1Clients: r1Client.join()