from socket import *
import time
import json
import statistics

def d(n,port):
	try:
		s = socket(AF_INET, SOCK_DGRAM) # SOCK_DGRAM opens a UDP socket
		s.bind(('', port)) # server binds port to listen packets from it
		end_to_end_delay = 0.0

		arr = []
		while True:
			req, peer = s.recvfrom(1000) # getting message and peer
			if(req.decode() == ''): # while loop breaks when empty string encountered
				break
			end_time = time.time() # timestamp when packet reaches destination
			end_to_end_delay = end_time - float(req.decode()) # end to end delay calculation
			end_to_end_delay *= 1000 # second to ms conversion
			arr.append(end_to_end_delay) # every iteration result is saved in an array

	except:
		print("Socket Error")


	finally:
		s.close()

		std = statistics.stdev(arr) # standart deviation calculation
		mean = statistics.mean(arr) # average calculation
		print("len", len(arr), "mean", mean, "std", std)


		# export delay arrays to json file
		data = {}

		data['delays'] = arr


		with open('data.json', 'w') as out:
			json.dump(data, out)


d(1000, 20033)
