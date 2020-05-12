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
class rdtSender(Thread):

	def __init__(self, fileName, fileReadSize, select, senderIP1, senderPort1, receiverIP1, receiverPort1,\
				 senderIP2, senderPort2, receiverIP2, receiverPort2):

		# common variables
		self.select = select
		self.timeOutInterval = 0.03  # basta 300 milisaniye
		self.chunks = self.createChunks(fileName, fileReadSize)
		self.windowSize = 10
		

		# variables for s-r1 communication
		self.senderIP1 = senderIP1
		self.senderPort1 = senderPort1
		self.receiverIP1 = receiverIP1
		self.receiverPort1 = receiverPort1
		self.s1 = socket(AF_INET,SOCK_DGRAM)
		self.r1 = socket(AF_INET,SOCK_DGRAM)
		self.r1.bind(("", self.receiverPort1))
		self.r1.settimeout(5)
		self.base1 = 0
		self.baseTime1 = 0
		self.baseLock1 = Lock()
		self.nextseqnum1 = 0
		self.termination1 = False

		# variables for s-r2 communication
		self.senderIP2 = senderIP2
		self.senderPort2 = senderPort2
		self.receiverIP2 = receiverIP2
		self.receiverPort2 = receiverPort2
		self.s2 = socket(AF_INET,SOCK_DGRAM)
		self.r2 = socket(AF_INET,SOCK_DGRAM)
		self.r2.bind(("", self.receiverPort2))
		self.r2.settimeout(5)		
		self.base2 = len(self.chunks) - 1
		self.baseTime2 = 0
		self.baseLock2 = Lock()		
		self.nextseqnum2 = len(self.chunks) - 1
		self.termination2 = False
		
		# Calling init function of thread class
		super().__init__()


	# Calculates and returns checksum of the given packet 
	def checkSum(self,packet):
		hash = hashlib.md5()
		hash.update(pickle.dumps(packet))
		return hash.digest()

	# Create chunks for the given file with the given fileReadSize
	# and store them to self.chunks array
	def createChunks(self,filename, fileReadSize):
		chunks = []
		with open(filename, 'rb') as f:

			data = f.read(fileReadSize)
			while(data != b''):
				chunks.append(data)
				data = f.read(fileReadSize)
		print("Total packet number to be sent is: 5.000.000 / 800 = ",len(chunks))
		return chunks

	def timeOut1(self):

		while True:
			time.sleep(0.02)

			with self.baseLock1:
				currentBase1 = self.base1
				currentNextSeqNum1 = self.nextseqnum1
				currentTimeOutInterval = self.timeOutInterval
				currentBaseTime1 = self.baseTime1
			
			if self.termination1 == True:
				#print("TimeOut_1 Thread bitti_termination")
				break

			if currentBase1 == len(self.chunks): # Data bitti
				#print("TimeOut_1 Thread bitti")
				break

			# Stop the timer (don't do anything in this case) 
			# when currentBase is equal to next sequence number
			if(currentBase1 == currentNextSeqNum1):
				continue

			currentTime1 = time.time()

			if ((currentTime1 - currentBaseTime1) >= currentTimeOutInterval): # timeOut oldu
				#print("Timeout_1 ",currentBase1)

				# Update base time with current time
				with self.baseLock1:
					self.baseTime1 = currentTime1

					# send packets from base to base+window number
					for i in range(currentBase1, currentNextSeqNum1):
						data = self.chunks[i]
						pkt = []
						pkt.append(i)
						pkt.append(data)
						pkt.append(self.checkSum(pkt))
						#print("Send timeout packet", i)
						self.s1.sendto(pickle.dumps(pkt), (self.senderIP1,self.senderPort1))

	def receive1(self):
		
		while True:
			try:
				pkt = self.r1.recv(1000)
			except:
				#print("##################### R1 TimeOut #######################")
				#print("Receiver_1 Bitti TimeOut")
				with self.baseLock1:
					self.termination1 = True
				break

			if pkt == b'':
				#print("Receive_1 Thread bitti_empty")
				#self.r.sendto("", peer)
				break

			receivedpacket = pickle.loads(pkt)
			#print("Received_1 ", receivedpacket[0])
			pktchecksum = receivedpacket[-1]
			receivedpacket = receivedpacket[:-1]

			if self.checkSum(receivedpacket) != pktchecksum: # corrupt
				#print("Packet_1 {} corrupted!".format(receivedpacket[0]))
				continue

			with self.baseLock1:
				self.base1 = receivedpacket[0] + 1
				#print("Newbase_1 {} -- NextSeqNum_1 {}".format(self.base1, self.nextseqnum1))
				if self.base1 == self.nextseqnum1:
					# stop timer, this is handled in timeout1 thread
					pass
				else:
					#start timer, change base time with the current time
					self.baseTime1 = time.time()
					pass

	def send1(self):

		while True:

			if self.termination1 == True:
				#print("Send_1 Thread bitti_termination")
				break

			with self.baseLock1:
				currentBase1 = self.base1

			if currentBase1 == len(self.chunks): # Data bitti
				#print("Send_1 Thread bitti_databitti")
				with self.baseLock1:
					self.termination1 = True					
				self.s1.sendto(b'', (self.senderIP1,self.senderPort1))
				break

			# Even if next sequence number exceedes data length,
			# wait for base to be equal to data length
			if self.nextseqnum1 >= len(self.chunks):
				continue

			data = self.chunks[self.nextseqnum1]

			# If the below condition is met, send the current packet
			if self.nextseqnum1 < (currentBase1 + self.windowSize):

				pkt = []
				pkt.append(self.nextseqnum1)
				pkt.append(data)
				pkt.append(self.checkSum(pkt))

				self.s1.sendto(pickle.dumps(pkt), (self.senderIP1,self.senderPort1))
				#print("Sent_1",self.nextseqnum1)

				if (currentBase1 == self.nextseqnum1):
					#start_timer, change base time with current time
					with self.baseLock1:
						self.baseTime1 = time.time()

				# Increase next sequence number
				with self.baseLock1:
					self.nextseqnum1 += 1

			else:
				#refuse_data
				pass

###################################################################################################################################

	def timeOut2(self):

		while True:
			time.sleep(0.02)

			with self.baseLock2:
				currentBase2 = self.base2
				currentNextSeqNum2 = self.nextseqnum2
				currentTimeOutInterval = self.timeOutInterval
				currentBaseTime2 = self.baseTime2
			
			if self.termination2 == True:
				#print("TimeOut_2 Thread bitti_termination")
				break
			
			if (currentBase2) == -1: # Data bitti
				#print("TimeOut_2 Thread bitti")
				break
			
			# Stop the timer (don't do anything in this case) 
			# when currentBase is equal to next sequence number
			if(currentBase2 == currentNextSeqNum2):
				continue

			currentTime2 = time.time()

			if ((currentTime2 - currentBaseTime2) >= currentTimeOutInterval): # timeOut oldu
				#print("Timeout_2 ",currentBase2)

				# Update base time with current time
				with self.baseLock2:
					self.baseTime2 = currentTime2

					# send packets base-window number to base
					for i in range(currentBase2, currentNextSeqNum2,-1):
						data = self.chunks[i]
						pkt = []
						pkt.append(i)
						pkt.append(data)
						pkt.append(self.checkSum(pkt))
						#print("Send timeout packet", i)
						self.s2.sendto(pickle.dumps(pkt), (self.senderIP2,self.senderPort2))

	def receive2(self):
		
		while True:
			try:
				pkt = self.r2.recv(1000)
			except:
				#print("##################### R2 TimeOut #######################")
				#print("Receiver_2 Bitti TimeOut")
				with self.baseLock2:
					self.termination2 = True
				break

			if pkt == b'':
				#print("Receive_2 Thread bitti_empty")
				#self.r.sendto("", peer)
				break

			receivedpacket = pickle.loads(pkt)
			#print("Received_2 ", receivedpacket[0])
			pktchecksum = receivedpacket[-1]
			receivedpacket = receivedpacket[:-1]

			if self.checkSum(receivedpacket) != pktchecksum: # corrupt
				#print("Packet_2 {} corrupted!".format(receivedpacket[0]))
				continue

			with self.baseLock2:
				self.base2 = receivedpacket[0] - 1
				#print("Newbase_2 {} -- NextSeqNum_2 {}".format(self.base2, self.nextseqnum2))
				if self.base2 == self.nextseqnum2:
					# stop timer, this is handled in timeout2 thread
					pass
				else:
					#start timer, change base time with the current time
					self.baseTime2 = time.time()
					pass

	def send2(self):

		while True:

			if self.termination2 == True:
				#print("Send_2 Thread bitti_termination")
				break

			with self.baseLock2:
				currentBase2 = self.base2	

			if currentBase2 == -1: # Data bitti
				#print("Send_2 Thread bitti_databitti")
				with self.baseLock2:
					self.termination2 = True		
				self.s2.sendto(b'', (self.senderIP2,self.senderPort2))
				break

			# Even if next sequence number exceedes data length,
			# wait for base to be equal to data length
			if self.nextseqnum2 <= -1:
				continue

			data = self.chunks[self.nextseqnum2]

			# If the below condition is met, send the current packet
			if self.nextseqnum2 > (currentBase2 - self.windowSize):

				pkt = []
				pkt.append(self.nextseqnum2)
				pkt.append(data)
				pkt.append(self.checkSum(pkt))

				self.s2.sendto(pickle.dumps(pkt), (self.senderIP2,self.senderPort2))
				#print("Sent_2",self.nextseqnum2)

				if (currentBase2 == self.nextseqnum2):
					#start_timer, change base time with current time
					with self.baseLock2:
						self.baseTime2 = time.time()

				# Increase next sequence number
				with self.baseLock2:
					self.nextseqnum2 -= 1

			else:
				#refuse_data
				pass

########################################################################################################################

	# To run send, receive and timeout threads for both r1 and r2 communications
	def run(self):

		timeOutThread1 = Thread(target=self.timeOut1)
		timeOutThread2 = Thread(target=self.timeOut2)
		receiveThread1 = Thread(target=self.receive1)
		receiveThread2 = Thread(target=self.receive2)
		sendThread1 = Thread(target=self.send1)
		sendThread2 = Thread(target=self.send2)
		timeOutThread1.start()
		timeOutThread2.start()
		receiveThread1.start()
		receiveThread2.start()
		sendThread1.start()
		sendThread2.start()
		timeOutThread1.join()
		timeOutThread2.join()
		receiveThread1.join()
		receiveThread2.join()
		sendThread1.join()
		sendThread2.join()
		self.s1.close()
		self.s2.close()
		self.r1.close()
		self.r2.close()

if __name__ == "__main__":

	fileName = "input.txt"
	chunkSize = 800
	select = "bos"
	senderPort1 = 20003
	receiverPort1 = 20033

	senderPort2 = 20004
	receiverPort2 = 20034

	#For testing on the local
	if(sys.argv[1] == "local"):		

		senderIP1 = 'localhost'
		receiverIP1 = 'localhost'

		senderIP2 = 'localhost'
		receiverIP2 = 'localhost'

	#For testing on the server machines
	elif(sys.argv[1] == "2"):
		senderIP1 = '10.10.1.2'
		receiverIP1 = '10.10.1.1'

		senderIP2 = '10.10.2.1'
		receiverIP2 = '10.10.2.2'

	mainProcess = rdtSender(fileName, chunkSize, select, senderIP1, senderPort1, receiverIP1, receiverPort1,\
								 senderIP2, senderPort2, receiverIP2, receiverPort2)
	mainProcess.start()