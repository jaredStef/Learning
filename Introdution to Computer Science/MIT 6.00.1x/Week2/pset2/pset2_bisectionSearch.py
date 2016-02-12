def runPayments(balance, annualInterestRate, payment):
	monthlyInterest = annualInterestRate / 12
	for month in range(0, 12):
		balance -= payment
		balance += (monthlyInterest * balance)
	return balance

from math import ceil

balance = 320000
annualInterestRate = 0.2
elipson = 0.01

lower = balance / 12
higher = balance * ((1 + (annualInterestRate / 12))**12 ) / 12

tries = 0

while True:
	midpoint =  (higher + lower) / 2
	payedLeft = runPayments(balance, annualInterestRate, midpoint)
	tries += 1
	if abs(payedLeft) <= elipson:
		print "The lowest payment is " + str(round(midpoint, 2))
		break
	elif payedLeft < 0:
		higher = midpoint
	elif payedLeft > 0:
		lower = midpoint
