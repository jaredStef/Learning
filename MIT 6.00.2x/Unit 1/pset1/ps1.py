###########################
# 6.00.2x Problem Set 1: Space Cows 

from ps1_partition import get_partitions
from collections import defaultdict
import time

#================================
# Part A: Transporting Space Cows
#================================

def load_cows(filename):
	"""
	Read the contents of the given file.  Assumes the file contents contain
	data in the form of comma-separated cow name, weight pairs, and return a
	dictionary containing cow names as keys and corresponding weights as values.

	Parameters:
	filename - the name of the data file as a string

	Returns:
	a dictionary of cow name (string), weight (int) pairs
	"""

	cow_dict = dict()

	f = open(filename, 'r')

	for line in f:
		line_data = line.split(',')
		cow_dict[line_data[0]] = int(line_data[1])
	return cow_dict


# Problem 1
def greedy_cow_transport(cows,limit=10):
	"""
	Uses a greedy heuristic to determine an allocation of cows that attempts to
	minimize the number of spaceship trips needed to transport all the cows. The
	returned allocation of cows may or may not be optimal.
	The greedy heuristic should follow the following method:

	1. As long as the current trip can fit another cow, add the largest cow that will fit
		to the trip
	2. Once the trip is full, begin a new trip to transport the remaining cows

	Does not mutate the given dictionary of cows.

	Parameters:
	cows - a dictionary of name (string), weight (int) pairs
	limit - weight limit of the spaceship (an int)

	Returns:
	A list of lists, with each inner list containing the names of cows
	transported on a particular trip and the overall list containing all the
	trips
	"""

	cowsByWeight = sorted(cows.items(), key=lambda x: x[1])
	trips = []

	# while there are still cows left
	while len(cowsByWeight) > 0:
		# generate trip
		tripVals = generateTrip(cowsByWeight, limit)

		# add generated trip
		trips.append(tripVals[0])
		#remove cows from trip
		cowsByWeight = tripVals[1]

	return trips

def generateTrip(cows, limit=10):
	limitCopy = limit
	onboardCows = []

	while limitCopy > 0:
		lastTryedIndex = -1
		try:
			while (cows[lastTryedIndex])[1] > limitCopy:
				if lastTryedIndex == -len(cows):
					return (onboardCows, cows)
				lastTryedIndex -= 1
			currentCow = cows[lastTryedIndex]
			onboardCows.append(currentCow[0])
			limitCopy -= currentCow[1]
			cows.remove(currentCow)
		except IndexError:
			if len(onboardCows) > 0:
				return (onboardCows, cows)

	return (onboardCows, cows)


# Problem 2
def brute_force_cow_transport(cows,limit=10):
	"""
	Finds the allocation of cows that minimizes the number of spaceship trips
	via brute force.  The brute force algorithm should follow the following method:

	1. Enumerate all possible ways that the cows can be divided into separate trips
	2. Select the allocation that minimizes the number of trips without making any trip
		that does not obey the weight limitation

	Does not mutate the given dictionary of cows.

	Parameters:
	cows - a dictionary of name (string), weight (int) pairs
	limit - weight limit of the spaceship (an int)

	Returns:
	A list of lists, with each inner list containing the names of cows
	transported on a particular trip and the overall list containing all the
	trips
	"""

	shortestTrip = []

	# go through all possible combinations
	for p in get_partitions(cows):
		validWeight = True
		# if a trip in a combination doesn't have valid weight set flag to false
		for trip in p:
			if not hasValidWeight(trip, cows, limit):
				validWeight = False

		# if is shortest length and valid set it
		# if shortest trip is blank ignore length
		if (len(p) < len(shortestTrip) or len(shortestTrip) == 0) and validWeight:
			shortestTrip = p

	return shortestTrip

def hasValidWeight(trip, cows, limit=10):
	total = 0
	for cow in trip:
		total += cows[cow]
	return total <= limit


# Problem 3
def compare_cow_transport_algorithms():
	"""
	Using the data from ps1_cow_data.txt and the specified weight limit, run your
	greedy_cow_transport and brute_force_cow_transport functions here. Use the
	default weight limits of 10 for both greedy_cow_transport and
	brute_force_cow_transport.

	Print out the number of trips returned by each method, and how long each
	method takes to run in seconds.

	Returns:
	Does not return anything.
	"""

	cows = load_cows("ps1_cow_data.txt")

	print 'Trying greedy algorithm...'
	greedyStart = time.time()
	greedySolution = len(greedy_cow_transport(cows, 10))
	print 'Length of solution was ' + str(greedySolution)
	greedyInterval = time.time() - greedyStart
	print 'Greedy algorithm took ' + str(greedyInterval) + ' seconds to run'

	print '------------------------------------'

	print 'Trying brute force algorithm...'
	bfStart = time.time()
	bfSolution = len(brute_force_cow_transport(cows, 10))
	print 'Length of solution was ' + str(bfSolution)
	bfInterval = time.time() - bfStart
	print 'Brute force algorithm took ' + str(bfInterval) + ' seconds to run'

	print '------------------------------------'

	print 'Brute force produced a ' + str(((float(greedySolution) / float(bfSolution)) - 1) * 100) + '% better solution'
	print 'and it took ' + str(bfInterval / greedyInterval) + ' times longer to run'

"""
Here is some test data for you to see the results of your algorithms with. 
Do not submit this along with any of your answers. Uncomment the last two
lines to print the result of your problem.
"""

cows = load_cows("ps1_cow_data.txt")
limit=10
print(cows)

print(greedy_cow_transport(cows, limit))
print(brute_force_cow_transport(cows, limit))

compare_cow_transport_algorithms()