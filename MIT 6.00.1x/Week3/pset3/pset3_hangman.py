# 6.00 Problem Set 3
#
# Hangman game
#

# -----------------------------------
# Helper code
# You don't need to understand this helper code,
# but you will have to know how to use the functions
# (so be sure to read the docstrings!)

import random
import string

WORDLIST_FILENAME = "words.txt"

def loadWords():
	"""
	Returns a list of valid words. Words are strings of lowercase letters.

	Depending on the size of the word list, this function may
	take a while to finish.
	"""
	print "Loading word list from file..."
	# inFile: file
	inFile = open(WORDLIST_FILENAME, 'r', 0)
	# line: string
	line = inFile.readline()
	# wordlist: list of strings
	wordlist = string.split(line)
	print "  ", len(wordlist), "words loaded."
	return wordlist

def chooseWord(wordlist):
	"""
	wordlist (list): list of words (strings)

	Returns a word from wordlist at random
	"""
	return random.choice(wordlist)

# end of helper code
# -----------------------------------

# Load the list of words into the variable wordlist
# so that it can be accessed from anywhere in the program
wordlist = loadWords()

def isWordGuessed(secretWord, lettersGuessed):
	'''
	secretWord: string, the word the user is guessing
	lettersGuessed: list, what letters have been guessed so far
	returns: boolean, True if all the letters of secretWord are in lettersGuessed;
	  False otherwise
	'''
	for letter in secretWord:
		if letter not in lettersGuessed:
			return False
	return True


def getGuessedWord(secretWord, lettersGuessed):

	'''
	secretWord: string, the word the user is guessing
	lettersGuessed: list, what letters have been guessed so far
	returns: string, comprised of letters and underscores that represents
	  what letters in secretWord have been guessed so far.
	'''
	currentString = ''
	for letter in secretWord:
		if letter in lettersGuessed:
			currentString = currentString + letter
		else:
			currentString = currentString + '_'
	return currentString

def getAvailableLetters(lettersGuessed):
	'''
	lettersGuessed: list, what letters have been guessed so far
	returns: string, comprised of letters that represents what letters have not
	  yet been guessed.
	'''
	alphabet = 'a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z'
	alphabet = alphabet.split(',')
	for letter in alphabet:
		if letter[0] in lettersGuessed:
			alphabet.remove(letter[0])
	return ''.join(alphabet)


def hangman(secretWord):
	'''
	secretWord: string, the secret word to guess.

	Starts up an interactive game of Hangman.

	* At the start of the game, let the user know how many
	  letters the secretWord contains.

	* Ask the user to supply one guess (i.e. letter) per round.

	* The user should receive feedback immediately after each guess
	  about whether their guess appears in the computers word.

	* After each round, you should also display to the user the
	  partially guessed word so far, as well as letters that the
	  user has not yet guessed.

	Follows the other limitations detailed in the problem write-up.
	'''
	print 'The word is ' + str(len(secretWord)) + ' characters long'
	lettersGuessed = []
	guessesRemaining = 8

	while True:
		letter = raw_input('Guess a letter: ').strip()
		if len(letter) != 1 and letter.isalnum():
			print 'Please enter a single character letter'
			continue
		if letter in lettersGuessed:
			print 'That letter has already been guessed'
			continue
		else:
			lettersGuessed.append(letter)
			if letter in secretWord:
				print 'good guess'
				if isWordGuessed(secretWord, lettersGuessed):
					print "You win!"
			else:
				print 'Poor guess'
				guessesRemaining -= 1
			# code updating things and telling user
			# code uses helper functions
			if guessesRemaining == 0:
				print 'Game Over!'
				print 'The correct word was ' + secretWord
				break
			print str(guessesRemaining) + ' guesses left!'
			print 'letters remaining ' + getAvailableLetters(lettersGuessed)
			print getGuessedWord(secretWord, lettersGuessed)
			print '------------------------------------------------'

secretWord = chooseWord(wordlist).lower()
hangman(secretWord)