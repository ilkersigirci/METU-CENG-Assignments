from socket import *
import time

def s(n,port, ip):
	try:
		c = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
		for i in range(n):

			time.sleep(0.001) # sleep in order to be able to let r3 catch every packet
			start_time = time.time() # timestamp before sending packet
			c.sendto((str(start_time)).encode(), (ip, port)) # send packet by giving destination ip and port

		for i in range(20):
			c.sendto(''.encode(), (ip,port)) # several empty strings sent for termination

	except:
		print("Socket Error")

	finally:
		c.close()

s(1000, 20003, '10.10.3.2')