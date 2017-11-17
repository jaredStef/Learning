def max_contig_sum(L):
	""" L, a list of integers, at least one positive
	Returns the maximum sum of a contiguous subsequence in L """
	
	#largestRange = ()
	largestSum = 0

	# Although the range is not required it is often
	# useful to have it, so one can print the subarray
	for i in range(len(L)):
		for j in range(len(L)): 
			intervalSum = sum(L[i: j+1]) 
			if intervalSum > largestSum: 
				largestSum = intervalSum
				#largestRange = (i, j+1)
	return largestSum