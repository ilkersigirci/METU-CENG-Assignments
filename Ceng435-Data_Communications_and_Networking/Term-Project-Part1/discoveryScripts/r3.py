from socket import *
from threading import Thread
import os,stat
import time, random
import statistics

def r3(n,ip,port):
	if   port == 20003: node = "s" # This is for output purposes
	elif port == 20033: node = "d"
	elif port == 20006: node = "r2"
	print("R3 WILL SEND MESSAGE TO: {} OVER {}".format(node, ip, port))
	c = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket 
	elapsed = [] # this list will hold all rtt values
	for i in range(n):
		"""
		if i%100 == 0:
			print("R3 SENT {} MESSAGES TO {}".format(i, node))
		"""
		start = time.time() # timestamp before sending packet
		c.sendto(b'message from r3', (ip, port)) # to send packet, destination ip and port must be specified
		result, peer = c.recvfrom(1000) # acknowledge is expected from server side
		done = time.time() # timestamp after getting acknowledge
		difference = done - start # rtt calculation
		elapsed.append(difference)
		#print("Result:" , result, "Peer:", peer)

	elapsedMean = statistics.mean(elapsed) # average of all rtts are calculated
	elapsedMean *= 1000 # Convert seconds to milliseconds
	print("Average delay between r3 and {} is : {} ms".format(node, elapsedMean))

r3Clients = []
r3Clients.append( Thread(target = r3, args=(1000,'10.10.3.1',20003)) )
r3Clients.append( Thread(target = r3, args=(1000,'10.10.7.1',20033)) )
r3Clients.append( Thread(target = r3, args=(1000,'10.10.6.1',20006)) )
for r3Client in r3Clients: r3Client.start() # different threads to do multiple tasks at the same time
for r3Client in r3Clients: r3Client.join()