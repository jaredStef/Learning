import re

occurances =  str(len(re.findall('(?=bob)', s)))
print "Number of times bob occurs is: " + occurances