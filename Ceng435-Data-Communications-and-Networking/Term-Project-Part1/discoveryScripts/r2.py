from socket import *
from threading import Thread
import os,stat
import time, random
import statistics

def r2(n,ip,port):

	if   port == 20002: node = "s" # This is for output purposes
	elif port == 20022: node = "d"
	print("R2 WILL SEND MESSAGE TO: {} OVER {}".format(node, ip, port))
	c = socket(AF_INET, SOCK_DGRAM)  # SOCK_DGRAM opens a UDP socket
	elapsed = [] # this list will hold all rtt values
	for i in range(n):
		"""
        if i%100 == 0:
            print("R2 SENT {} MESSAGES TO {}".format(i, node))
		"""
		start = time.time() # timestamp before sending packet
		c.sendto(b'message from r2', (ip, port))  # to send packet, destination ip and port must be specified
		result, peer = c.recvfrom(1000) # acknowledge is expected from server side
		done = time.time() # timestamp after getting acknowledge
		difference = done - start # rtt calculation
		elapsed.append(difference)
		#print("Result:" , result, "Peer:", peer)

	elapsedMean = statistics.mean(elapsed) # average of all rtts are calculated
	elapsedMean *= 1000 # Convert seconds to milliseconds
	print("Average delay between r2 and {} is : {} ms".format(node, elapsedMean))

def r2_server(n,port):

	if   port == 20005: node = "r1" # This is for output purposes
	elif port == 20006: node = "r3"
	try:
		r2 = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
		r2.bind(('', port)) # server binds port to listen packets from it
		print("R2_SERVER IS LISTENING THE PORT: {}".format(port))
	except:
		print("R2_SERVER CAN NOT BIND THE PORT: ".format(port))

	finally:
		for i in range(n):
			req, peer = r2.recvfrom(1000) # getting message and peer
			"""
			if i%100 == 0:
				print("R2_SERVER RECEIVED {} MESSAGES FROM {}".format(i, node))
			#print("request from ",req, " from ", peer)
			"""
			r2.sendto(req, peer) # same message packet sent as acknowledge
		r2.close()


r2Clients = []
r2Clients.append( Thread(target = r2, args=(1000,'10.10.2.2',20002)) )
r2Clients.append( Thread(target = r2, args=(1000,'10.10.5.2',20022)) )

r2Servers = []
r2Servers.append(Thread(target = r2_server, args=(1000,20005)))
r2Servers.append(Thread(target = r2_server, args=(1000,20006)))

for r2Client in r2Clients: r2Client.start() # different threads to do multiple tasks at the same time
for r2Server in r2Servers: r2Server.start()

for r2Client in r2Clients: r2Client.join() # different threads to do multiple tasks at the same time
for r2Server in r2Servers: r2Server.join()

