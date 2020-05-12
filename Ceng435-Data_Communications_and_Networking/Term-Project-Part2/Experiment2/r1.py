import time
from socket import *
from threading import *
import pickle
import sys

def r1(incoming_port, outgoing_port, destination_ip, select):

	s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
	s.bind(('', incoming_port)) # server binds port to listen packets from it

	while True:

		req, peer = s.recvfrom(1000) # getting message and peer

		if(req == b''): # when empty string is encountered, termination message is forwarded to destination several times
			for i in range(20):
				s.sendto(req, (destination_ip, outgoing_port)) # while loop breaks when empty string encountered
			
			continue # instead of break we continued for infinite loop

		pkt = pickle.loads(req)

		#for seeing sending and receiving packets 
		""" if select == "first":
			print("Received seq ",pkt[0])
		if select == "second":
			print("Received ack ",pkt[0]) """
		s.sendto(req, (destination_ip, outgoing_port)) # send packet by giving destination ip and port
		


if(sys.argv[1] == "local"):		

		destination_ip1 = 'localhost'
		destination_ip2 = 'localhost'

elif(sys.argv[1] == "2"):
	destination_ip1 = '10.10.4.2'
	destination_ip2 = '10.10.1.1'

r1Threads = []
r1Threads.append( Thread(target = r1, args=(20003, 20035, destination_ip1, "first")) )
r1Threads.append( Thread(target = r1, args=(20005, 20033, destination_ip2, "second")) )
for r1T in r1Threads: r1T.start() # different threads to do multiple tasks at the same time
for r1T in r1Threads: r1T.join()