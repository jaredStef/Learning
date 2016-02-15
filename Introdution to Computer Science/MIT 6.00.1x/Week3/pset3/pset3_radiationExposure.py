
def f(x):
	import math
	return 10*math.e**(math.log(0.5)/5.27 * x)

def radiationExposure(start, stop, step):
	totalExposure = 0
	for i in range(start, stop):
		totalExposure += f(float(i))*float(step)
	return totalExposure

