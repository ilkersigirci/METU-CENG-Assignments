def readTrc(file):
	data = []
	with open(file,'r') as trc:
		for row in trc:
			data.append(float(row))
		return data
	
def powerTrace(data):
	
	exp = ""
	count = 0

	for row in data:
		row = float(row)
		if row > 7.5:
			count += 1
		else:
			if count >= 75 and count < 125:
				exp += '0'
			elif count >= 125:
				exp += '1'

			count = 0
	return exp

def modPower(b,exp,n):
	r = 1
	for bit in exp:
		r = (r*r) % n
		if bit == '1':
			r = (b*r) % n
	return r

def main():
	
	message = int(raw_input(),16)
	n = int(raw_input(),16)
	data = readTrc("ptrace.trc")
	exponent = powerTrace(data)
	text = modPower(message, exponent, n)
	print '%s' % format(text, 'x').decode('hex')

main()