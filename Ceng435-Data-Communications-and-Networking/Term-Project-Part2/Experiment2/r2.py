import time
from socket import *
from threading import *
import pickle
import sys

def r2(incoming_port, outgoing_port, destination_ip, select):

	s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
	s.bind(('', incoming_port)) # server binds port to listen packets from it

	while True:

		req, peer = s.recvfrom(1000) # getting message and peer

		if(req == b''): # when empty string is encountered, termination message is forwarded to destination several times
			for i in range(20):
				s.sendto(req, (destination_ip, outgoing_port)) # while loop breaks when empty string encountered
			
			continue  # instead of break we continued for infinite loop

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
	destination_ip1 = '10.10.5.2'
	destination_ip2 = '10.10.2.2'

r2Threads = []
r2Threads.append( Thread(target = r2, args=(20004, 20054, destination_ip1, "first")) )
r2Threads.append( Thread(target = r2, args=(20008, 20034, destination_ip2, "second")) )
for r2T in r2Threads: r2T.start() # different threads to do multiple tasks at the same time
for r2T in r2Threads: r2T.join()