from socket import *
from threading import *
import os,stat
import time, random
import hashlib
import pickle
import sys

class rdtReceiver(Thread):

	def __init__(self,outputFileName, ip, incoming_port, outgoing_port):

		self.ip = ip
		self.incoming_port = incoming_port
		self.outgoing_port = outgoing_port
		self.outputFileName = outputFileName
		self.d = socket(AF_INET,SOCK_DGRAM)
		self.d.bind(("", self.incoming_port))
		#self.d.settimeout(0.001)
		self.expectedseqnum = 1
		self.receivedData = []

		super().__init__()

	def checkSum(self,packet):
		hash = hashlib.md5()
		hash.update(pickle.dumps(packet))
		return hash.digest()

	def receiver(self):
		while True:
			pkt = self.d.recv(1000)
			peer = (self.ip, self.outgoing_port)
			if pkt == b'':
				self.d.sendto(b'',peer)
				break

			receivedPacket = pickle.loads(pkt)
			pktChecksum = receivedPacket[-1]
			receivedPacket = receivedPacket[:-1]

			if self.checkSum(receivedPacket) != pktChecksum: # corrupt
				print("Received packet {} is corrupted!".format(receivedPacket[0]))
				continue

			if receivedPacket[0] != self.expectedseqnum: # out of order
				#print("Received packet {} is out of order!".format(receivedPacket[0]))
				sendPacket = []
				sendPacket.append(self.expectedseqnum-1) #TODO: -1 geri bak
				sendPacket.append(self.checkSum(sendPacket))
				
				self.d.sendto(pickle.dumps(sendPacket), peer)
				#print("(re)send ACK ", self.expectedseqnum-1) 
				continue

			#print("Received packet {} is  in order!".format((receivedPacket[0])))
			sendPacket = []
			sendPacket.append(self.expectedseqnum)
			sendPacket.append(self.checkSum(sendPacket))
			self.d.sendto(pickle.dumps(sendPacket), peer)
			#print("send ACK ", self.expectedseqnum)
			self.expectedseqnum += 1

			if receivedPacket[1]: # if inorder received data isn't empty, append it to data list
				self.receivedData.append(receivedPacket[1])


	def run(self):
		startTime = time.time()
		receiverThread = Thread(target=self.receiver)
		receiverThread.start()
		receiverThread.join()
		self.d.close()
		endTime = time.time()
		print("File transfer time ", endTime - startTime)

		with open(outputFileName, "wb") as outputFile:
			index = 0
			for i in self.receivedData:
				#print("index ", index)
				index += 1
				outputFile.write(i) 

if __name__ == "__main__":

	if( sys.argv[1] == '1'):


		ip = '10.10.7.2'
		incoming_port = 20033
		outgoing_port = 20034
		outputFileName = "output.txt"

		mainProcess = rdtReceiver(outputFileName, ip, incoming_port, outgoing_port)
		mainProcess.start()
