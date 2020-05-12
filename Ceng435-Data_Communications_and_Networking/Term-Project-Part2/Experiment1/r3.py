import time
from socket import *
from threading import *
import pickle
import sys

def r3(incoming_port, outgoing_port, destination_ip, select):
	""" try:
		s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
		s.bind(('', incoming_port)) # server binds port to listen packets from it

		while True:

			req, peer = s.recvfrom(1000) # getting message and peer
			s.sendto(req, (destination_ip, outgoing_port)) # send packet by giving destination ip and port
			if(req.decode() == ''): # when empty string is encountered, termination message is forwarded to destination several times
				for i in range(20):
					s.sendto(req, (destination_ip, outgoing_port)) # while loop breaks when empty string encountered
				break

	except:
		print("Socket Error")

	finally:
		s.close() """
	
	s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
	s.bind(('', incoming_port)) # server binds port to listen packets from it

	while True:

		req, peer = s.recvfrom(1000) # getting message and peer

		if(req == b''): # when empty string is encountered, termination message is forwarded to destination several times
			for i in range(20):
				s.sendto(req, (destination_ip, outgoing_port)) # while loop breaks when empty string encountered
			#break
			continue

		pkt = pickle.loads(req)
		""" if select == "first":
			print("Received seq ",pkt[0])
		if select == "second":
			print("Received ack ",pkt[0]) """
		s.sendto(req, (destination_ip, outgoing_port)) # send packet by giving destination ip and port
		


r3Threads = []
r3Threads.append( Thread(target = r3, args=(20003, 20033, '10.10.7.1',"first")) )
r3Threads.append( Thread(target = r3, args=(20034, 20004, '10.10.3.1',"second")) )
for r3T in r3Threads: r3T.start() # different threads to do multiple tasks at the same time
for r3T in r3Threads: r3T.join()