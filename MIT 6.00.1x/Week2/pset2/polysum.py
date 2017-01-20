import math

def polysum(n, s):
	'''
	:param n: The number of sides in the shape
	:param s: The length of each side
	:return: The sum of the area and perimeter of the polygon
	'''
	perimeter = s * n
	apothem = s / (2 * tan(180/n))
	area = (apothem * perimeter) / 2
	return area + perimeter

