import csv
from fractions import gcd

def readCsv(file):
	with open(file) as csvFile:
		data = csv.reader(csvFile, delimiter=',')
		return [int(row[1],16) for row in data]

def egcd(a, b):
    lastremainder, remainder = abs(a), abs(b)
    x, lastx, y, lasty = 0, 1, 1, 0
    while remainder:
        lastremainder, (quotient, remainder) = remainder, divmod(lastremainder, remainder)
        x, lastx = lastx - quotient*x, x
        y, lasty = lasty - quotient*y, y
    return lastremainder, lastx * (-1 if a < 0 else 1), lasty * (-1 if b < 0 else 1)

def modinv(a, m):
    g, x, y = egcd(a, m)
    return x % m

def commonModulusAttack(c1, c2, e1, e2, n):
	s1 = modinv(e1,e2)
	s2 = (gcd(e1,e2) - e1 * s1) / e2
	m1 = pow(c1,s1,n)
	m2 = pow(modinv(c2, n),int(-s2),n)
	return (m1 * m2) % n

def main():

	c1,c2,e1,e2,n = readCsv("crackme.csv")

	message = commonModulusAttack(c1, c2, e1, e2, n)
	print('%s' % format(message, 'x').decode('hex'))

main()