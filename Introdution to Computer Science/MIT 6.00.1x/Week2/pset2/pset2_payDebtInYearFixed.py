def runPayments(balance, annualInterestRate, payment):
	monthlyInterest = annualInterestRate / 12
	for month in range(0, 12):
		balance -= payment
		balance += (monthlyInterest * balance)
	return balance

ans = 10
incrementSize = 10

while True:
	remaining = runPayments(4773, 0.2, ans)
	if remaining == 0:
		print "Real Min to pay is: " + str(ans)
	elif remaining < 0:
		print "Min to nearest 10 is " + str(ans)
		break
		ans += incrementSize
