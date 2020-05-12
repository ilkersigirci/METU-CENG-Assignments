import time
from socket import *


def r3(incoming_port, outgoing_port, destination_ip):
	try:
		s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
		s.bind(('', incoming_port)) # server binds port to listen packets from it

		d = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket

		while True:

			req, peer = s.recvfrom(1000) # getting message and peer
			d.sendto(req, (destination_ip, outgoing_port)) # send packet by giving destination ip and port
			if(req.decode() == ''): # when empty string is encountered, termination message is forwarded to destination several times
				for i in range(20):
					d.sendto(req, (destination_ip, outgoing_port)) # while loop breaks when empty string encountered
				break

	except:
		print("Socket Error")

	finally:
		s.close()
		d.close()


r3(20003, 20033, '10.10.7.1')