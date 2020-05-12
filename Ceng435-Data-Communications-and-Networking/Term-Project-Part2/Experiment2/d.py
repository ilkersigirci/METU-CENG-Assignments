from socket import *
from threading import *
import os,stat
import time, random
import hashlib
import pickle
import sys

# We inherited Thread class, to make the code more readable
# both for us and for the assistants.
# Thanks to this class based design, we didn't use 
# any global variables, instead we declare them as class instance variable
class rdtReceiver(Thread):

	def __init__(self,outputFileName, ip1, incoming_port1, outgoing_port1, ip2, incoming_port2, outgoing_port2):

		# common variables
		self.outputFileName = outputFileName
		self.check = Lock()	

		# variables for d-r1 communication
		self.ip1 = ip1
		self.incoming_port1 = incoming_port1
		self.outgoing_port1 = outgoing_port1		
		self.d1 = socket(AF_INET,SOCK_DGRAM)
		self.d1.bind(("", self.incoming_port1))
		self.d1.settimeout(5)
		self.expectedseqnum1 = 0
		self.receivedData1 = []

		# variables for d-r2 communication
		self.ip2 = ip2
		self.incoming_port2 = incoming_port2
		self.outgoing_port2 = outgoing_port2		
		self.d2 = socket(AF_INET,SOCK_DGRAM)
		self.d2.bind(("", self.incoming_port2))
		self.d2.settimeout(5)
		self.expectedseqnum2 = 6249
		self.receivedData2 = []

		# Calling init function of thread class
		super().__init__()

	# Function that calculates and returns checksum of the given packet 
	def checkSum(self,packet):
		hash = hashlib.md5()
		hash.update(pickle.dumps(packet))
		return hash.digest()

	def receiver1(self):
		while True:

			# Check if the windows are collapsed
			with self.check:
				if self.expectedseqnum1 > self.expectedseqnum2:
					#print("Windows are collapsed in 1")
					#print("expected1 {} -- expected2 {}"
							#.format(self.expectedseqnum1,self.expectedseqnum2))
					break
			
			try:
				pkt = self.d1.recv(1000)
			# D1 socket is timeout, end the receiver1 thread
			except:
				#print("##################### D1 TimeOut #######################")
				break

			peer = (self.ip1, self.outgoing_port1)
			if pkt == b'':
				#print("Receiver_1 Thread bitti")
				self.d1.sendto(b'',peer)
				break

			receivedPacket = pickle.loads(pkt)
			pktChecksum = receivedPacket[-1]
			receivedPacket = receivedPacket[:-1]

			if self.checkSum(receivedPacket) != pktChecksum: # corrupt
				#print("Received_1 packet is corrupted ", receivedPacket[0])
				continue

			if receivedPacket[0] != self.expectedseqnum1: # out of order
				#print("Received_1 packet is out of order ", receivedPacket[0])
				sendPacket = []
				sendPacket.append(self.expectedseqnum1-1)
				sendPacket.append(self.checkSum(sendPacket))
				
				self.d1.sendto(pickle.dumps(sendPacket), peer)
				#print("(re)send_1 ACK ", self.expectedseqnum1-1)
				continue

			#print("Received_1 packet is inorder ", receivedPacket[0])
			sendPacket = []
			sendPacket.append(self.expectedseqnum1)
			sendPacket.append(self.checkSum(sendPacket))
			self.d1.sendto(pickle.dumps(sendPacket), peer)
			#print("send_1 ACK ", self.expectedseqnum1)
			self.expectedseqnum1 += 1

			if receivedPacket[1]: # if inorder received data isn't empty, append it to data list
				self.receivedData1.append(receivedPacket[1])


	def receiver2(self):
		while True:

			# Check if the windows are collapsed
			with self.check:
				if self.expectedseqnum1 > self.expectedseqnum2:
					#print("Windows are collapsed in 2")
					#print("expected1 {} -- expected2 {}"
							#.format(self.expectedseqnum1,self.expectedseqnum2))
					break
			try:
				pkt = self.d2.recv(1000)
			# D2 socket is timeout, end the receiver2 thread
			except:
				#print("##################### D2 TimeOut #######################")
				break

			peer = (self.ip2, self.outgoing_port2)
			if pkt == b'':
				#print("Receiver_2 Thread bitti")
				self.d2.sendto(b'',peer)
				break

			receivedPacket = pickle.loads(pkt)
			pktChecksum = receivedPacket[-1]
			receivedPacket = receivedPacket[:-1]

			if self.checkSum(receivedPacket) != pktChecksum: # corrupt
				#print("Received_2 packet is corrupted ", receivedPacket[0])
				continue

			if receivedPacket[0] != self.expectedseqnum2: # out of order
				#print("Received_2 packet is out of order ", receivedPacket[0])
				sendPacket = []
				sendPacket.append(self.expectedseqnum2+1)
				sendPacket.append(self.checkSum(sendPacket))
				
				self.d2.sendto(pickle.dumps(sendPacket), peer)
				#print("(re)send_2 ACK ", self.expectedseqnum2+1) 
				continue

			#print("Received_2 packet is inorder ", receivedPacket[0])
			sendPacket = []
			sendPacket.append(self.expectedseqnum2)
			sendPacket.append(self.checkSum(sendPacket))
			self.d2.sendto(pickle.dumps(sendPacket), peer)
			#print("send_2 ACK ", self.expectedseqnum2)
			self.expectedseqnum2 -= 1

			if receivedPacket[1]: # if inorder received data isn't empty, append it to data list
				self.receivedData2.append(receivedPacket[1])


	def run(self):
		startTime = time.time()
		receiverThread1 = Thread(target=self.receiver1)
		receiverThread2 = Thread(target=self.receiver2)
		receiverThread1.start()
		receiverThread2.start()
		receiverThread1.join()
		receiverThread2.join()
		self.d1.close()
		self.d2.close()
		endTime = time.time()
		print("File transfer time ", endTime - startTime)

		d1Len = len(self.receivedData1)
		d2Len = len(self.receivedData2)

		if d1Len + d2Len > 6250: # for handling duplicate one packet
			self.receivedData2 = self.receivedData2[:-1]
		
		print("Packets length from r1: {}, Packets length from r2: {}" \
			.format(len(self.receivedData1),len(self.receivedData2)))

		with open(outputFileName, "wb") as outputFile:
			
			for i in self.receivedData1:
				outputFile.write(i)

			for i in reversed(self.receivedData2):
				outputFile.write(i)

if __name__ == "__main__":

	outputFileName = "output.txt"

	incoming_port1 = 20035
	outgoing_port1 = 20005
	
	incoming_port2 = 20054
	outgoing_port2 = 20008

	# To test on the local
	if(sys.argv[1] == "local"):		

		ip1 = 'localhost'
		ip2 = 'localhost'

	# To test on the server machines
	elif( sys.argv[1] == '2'):

		ip1 = '10.10.4.1'
		ip2 = '10.10.5.1'		

	mainProcess = rdtReceiver(outputFileName, ip1, incoming_port1, outgoing_port1, \
								ip2, incoming_port2, outgoing_port2)
	mainProcess.start()
