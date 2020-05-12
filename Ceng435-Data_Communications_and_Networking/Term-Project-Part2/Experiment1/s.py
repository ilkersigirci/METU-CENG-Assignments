from socket import *
from threading import *
import os,stat
import time, random
import hashlib
import pickle
import sys

class rdtSender(Thread):

	def __init__(self, fileName, fileReadSize, senderIP, senderPort, receiverIP, receiverPort):

		self.senderIP = senderIP
		self.senderPort = senderPort
		self.receiverIP = receiverIP
		self.receiverPort = receiverPort
		self.s = socket(AF_INET,SOCK_DGRAM)
		self.r = socket(AF_INET,SOCK_DGRAM)
		self.r.bind(("", self.receiverPort))
		#self.s.settimeout(10)
		self.estimatedRTT = 0
		self.devRTT = 0
		self.baseTime = 0
		self.timeOutInterval = 0.03  # basta 300 milisaniye -> arbitrary
		self.baseLock = Lock()
		self.base = 1
		self.nextseqnum = 1
		self.windowSize = 10
		self.chunks = self.createChunks(fileName, fileReadSize)
		super().__init__()


	def checkSum(self,packet):
		hash = hashlib.md5()
		hash.update(pickle.dumps(packet))
		return hash.digest()

	def calcTimeoutInterval(self,sampleRTT): #FIXME: her pakette degiscek sekilde degistir
		self.estimatedRTT = (0.875 * self.estimatedRTT) + (0.125 * sampleRTT)
		self.devRTT = (0.75 * self.devRTT) + (0.75 * abs(sampleRTT - self.estimatedRTT))
		return self.estimatedRTT + (4 * self.devRTT)

	def createChunks(self,filename, fileReadSize):
		chunks = []
		with open(filename, 'rb') as f:

			data = f.read(fileReadSize)
			while(data != b''):
				chunks.append(data)
				data = f.read(fileReadSize)
		#print(len(chunks))
		return chunks

	def timeOut(self):

		while True:
			time.sleep(0.02)

			with self.baseLock:
				currentBase = self.base
				currentNextSeqNum = self.nextseqnum
				currentTimeOutInterval = self.timeOutInterval
				currentBaseTime = self.baseTime
			
			if (currentBase-1) == len(self.chunks): # Data bitti
				print("TimeOut Thread bitti")
				break

			if(currentBase == currentNextSeqNum):
				continue

			currentTime = time.time()

			if ((currentTime - currentBaseTime) >= currentTimeOutInterval): # timeOut oldu
				#print("Packet {} is timeout".format(currentBase))

				with self.baseLock:
					self.baseTime = currentTime

					#base'dan window number kadar gonder
					for i in range(currentBase, currentNextSeqNum): #FIXME: -1 olaylarina dikkat
						data = self.chunks[i-1]
						pkt = []
						pkt.append(i)
						pkt.append(data)
						pkt.append(self.checkSum(pkt))
						#print("Send timeout packet", i)
						self.s.sendto(pickle.dumps(pkt), (self.senderIP,self.senderPort))


	def receive(self):
		
		while True:
			pkt, peer =  self.r.recvfrom(1000)
			if pkt == b'':
				print("Receive Thread bitti")
				#self.r.sendto("", peer)
				break

			receivedpacket = pickle.loads(pkt)
			#print("Received ", receivedpacket[0])
			pktchecksum = receivedpacket[-1]
			receivedpacket = receivedpacket[:-1]

			if self.checkSum(receivedpacket) != pktchecksum: # corrupt
				#print("Packet {} corrupted!".format(receivedpacket[0]))
				continue

			with self.baseLock:
				self.base = receivedpacket[0] + 1
				#print("Newbase {} NextSeqNum {}".format(self.base, self.nextseqnum))
				if self.base == self.nextseqnum:
					# stop timer
					pass
				else:
					#start timer
					self.baseTime = time.time()
					pass

	def send(self):
		totalPacketCount = len(self.chunks)

		while True:

			with self.baseLock:
				currentBase = self.base	

			if (currentBase-1) == len(self.chunks): # Data bitti
				print("Send Thread bitti")
				self.s.sendto(b'', (self.senderIP,self.senderPort))
				break

			if self.nextseqnum-1 >= len(self.chunks):
				continue

			data = self.chunks[self.nextseqnum-1]

			#print("currentbase", currentBase, self.nextseqnum)
			if self.nextseqnum < (currentBase + self.windowSize):

				pkt = []
				pkt.append(self.nextseqnum)
				pkt.append(data)
				pkt.append(self.checkSum(pkt))

				self.s.sendto(pickle.dumps(pkt), (self.senderIP,self.senderPort))
				#print("Packet {} sent".format(self.nextseqnum))

				if (currentBase == self.nextseqnum):
					#start_timer
					with self.baseLock:
						self.baseTime = time.time()

				with self.baseLock:
					self.nextseqnum += 1

			else:
				#refuse_data
				#continue da ayni hesap
				pass

	def run(self):

		timeOutThread = Thread(target=self.timeOut)
		receiveThread = Thread(target=self.receive)
		sendThread = Thread(target=self.send)
		timeOutThread.start()
		receiveThread.start()
		sendThread.start()
		timeOutThread.join()
		receiveThread.join()
		sendThread.join()
		self.s.close()

if __name__ == "__main__":

	if( sys.argv[1] == '1'):

		fileName = "input.txt"
		chunkSize = 800

		# senderIP, senderPort, receiverIP, receiverPort
		senderIP = '10.10.3.2'
		senderPort = 20003

		receiverIP = '10.10.3.1'
		receiverPort = 20004

		mainProcess = rdtSender(fileName, chunkSize, senderIP, senderPort, receiverIP, receiverPort)
		mainProcess.start()
