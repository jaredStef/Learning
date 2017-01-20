vowels = 0

def isVowel(letter):
	vowels = ['a', 'e', 'i', 'o', 'u']
	return letter in vowels


for char in s:
	if isVowel(char):
		vowels += 1

print "Number of vowels: " + str(vowels)
