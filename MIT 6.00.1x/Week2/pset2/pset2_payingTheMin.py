balance = 4213
annualInterestRate = 0.2
monthlyPaymentRate = 0.04
totalPayed = 0

for month in range(0, 12):
	toPay = balance * monthlyPaymentRate
	balance -= toPay
	totalPayed += toPay
	interest = (annualInterestRate / 12) * balance
	balance += interest
	print "Month: " + str(month)
	print "Minimum monthly payment: %.2f  " % toPay
	print "Remaining balance: %.2f " % balance
	print "\n"

print "Remaining Balance: %.2f" % balance
print "Total Payed: %.2f " % totalPayed
