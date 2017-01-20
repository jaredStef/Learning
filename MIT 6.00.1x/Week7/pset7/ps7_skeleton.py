import random as rand
import string
import math

class AdoptionCenter:
	"""
	The AdoptionCenter class stores the important information that a
	client would need to know about, such as the different numbers of
	species stored, the location, and the name. It also has a method to adopt a pet.
	"""

	def __init__(self, name, species_types, location):
		self.name = name
		self.species_types = species_types
		self.location = location

	def get_number_of_species(self, animal):
		try:
			return self.species_types[animal]
		except KeyError:
			return 0

	def get_location(self):
		return self.location

	def get_species_count(self):
		return self.species_types.copy()

	def get_name(self):
		return self.name

	def adopt_pet(self, species):
		self.species_types[species] -= 1


class Adopter(object):
	"""
	Adopters represent people interested in adopting a species.
	They have a desired species type that they want, and their score is
	simply the number of species that the shelter has of that species.
	"""
	def __init__(self, name, desired_species):
		self.name = name
		self.desired_species = desired_species

	def get_name(self):
		return self.name

	def get_desired_species(self):
		return self.desired_species

	def get_score(self, adoption_center):
		try:
			return adoption_center.get_species_count()[self.desired_species]
		except KeyError:
			return 0



class FlexibleAdopter(Adopter):
	"""
	A FlexibleAdopter still has one type of species that they desire,
	but they are also alright with considering other types of species.
	considered_species is a list containing the other species the adopter will consider
	Their score should be 1x their desired species + .3x all of their desired species
	"""
	def __init__(self, name, desired_species, considered_species):
		super(FlexibleAdopter, self).__init__(name, desired_species)
		self.considered_species = considered_species
	def get_score(self, adoption_center):
		superScore = Adopter(self.name, self.desired_species).get_score(adoption_center)
		numOther = 0
		try:
			for species in self.considered_species:
				numOther += adoption_center.get_species_count()[species]
			if numOther > 0:
				return superScore + 0.3 * numOther
			else:
				return superScore + 0.3
		except KeyError:
			return 0


class FearfulAdopter(Adopter):
	"""
	A FearfulAdopter is afraid of a particular species of animal.
	If the adoption center has one or more of those animals in it, they will
	be a bit more reluctant to go there due to the presence of the feared species.
	Their score should be 1x number of desired species - .3x the number of feared species
	"""
	def __init__(self, name, desired_species, feared_species):
		super(FearfulAdopter, self).__init__(name, desired_species)
		self.feared_species = feared_species

	def get_score(self, adoption_center):
		try:
			superScore = Adopter(self.name, self.desired_species).get_score(adoption_center)
			numFeared = adoption_center.get_species_count()[self.feared_species]
			return superScore - 0.3 * numFeared
		except KeyError:
			return 0



class AllergicAdopter(Adopter):
	"""
	An AllergicAdopter is extremely allergic to a one or more species and cannot
	even be around it a little bit! If the adoption center contains one or more of
	these animals, they will not go there.
	Score should be 0 if the center contains any of the animals, or 1x number of desired animals if not
	"""
	def __init__(self, name, desired_species, allergic_species):
		super(AllergicAdopter, self).__init__(name, desired_species)
		self.allergic_species = allergic_species

	def get_score(self, adoption_center):
		try:
			for species in self.allergic_species:
				if adoption_center.get_species_count()[species] > 0:
					return 0
			return Adopter(self.name, self.desired_species).get_score(adoption_center)
		except KeyError:
			return 0

class MedicatedAllergicAdopter(AllergicAdopter):
	"""
	A MedicatedAllergicAdopter is extremely allergic to a particular species
	However! They have a medicine of varying effectiveness, which will be given in a dictionary
	To calculate the score for a specific adoption center, we want to find what is the most allergy-inducing species that the adoption center has for the particular MedicatedAllergicAdopter.
	To do this, first examine what species the AdoptionCenter has that the MedicatedAllergicAdopter is allergic to, then compare them to the medicine_effectiveness dictionary.
	Take the lowest medicine_effectiveness found for these species, and multiply that value by the Adopter's calculate score method.
	"""
	def __init__(self, name, desired_species, allergic_species, medicine_effectiveness):
		super(MedicatedAllergicAdopter, self).__init__(name, desired_species, allergic_species)
		self.medicine_effectiveness = medicine_effectiveness

	def get_score(self, adoption_center):
		# find what species the center has that is alergic to
		# compare to medicine_effectivness dict (String: Float)
		# the lowest found * adopters score is returned
		center_species = adoption_center.get_species_count()
		lowest = 0
		try:
			for species in center_species:
				if self.medicine_effectiveness[species] * center_species[species] < lowest:
					lowest = self.medicine_effectiveness[species] * center_species[species]
			superScore = Adopter(self.name, self.desired_species).get_score(adoption_center)
			if lowest > 0:
				return lowest * superScore
			else:
				return superScore
		except KeyError:
			return 0

class SluggishAdopter(Adopter):
	"""
	A SluggishAdopter really dislikes travelleng. The further away the
	AdoptionCenter is linearly, the less likely they will want to visit it.
	Since we are not sure the specific mood the SluggishAdopter will be in on a
	given day, we will asign their score with a random modifier depending on
	distance as a guess.
	Score should be
	If distance < 1 return 1 x number of desired species
	elif distance < 3 return random between (.7, .9) times number of desired species
	elif distance < 5. return random between (.5, .7 times number of desired species
	else return random between (.1, .5) times number of desired species
	"""
	def __init__(self, name, desired_species, location):
		super(SluggishAdopter, self).__init__(name, desired_species)
		self.location = location

	def get_linear_distance(adopter, to_location):
		return math.sqrt(math.pow(to_location[0] - adopter.location[0], 2) + math.pow(to_location[1] - adopter.location[1], 2))

	def get_score(self, adoption_center):
		distance = SluggishAdopter.get_linear_distance(self ,adoption_center.location)
		desired_species_amount = adoption_center.get_number_of_species(self.desired_species)
		if distance < 1:
			return desired_species_amount
		elif distance < 3 and distance >= 1:
			random = rand.uniform(0.7, 0.9)
			return random * desired_species_amount
		elif distance < 5 and distance >= 3:
			random = rand.uniform(0.5, 0.7)
			return random * desired_species_amount
		elif distance >= 5:
			random = rand.uniform(0.1, 0.5)
			return random * desired_species_amount

def get_ordered_adoption_center_list(adopter, list_of_adoption_centers):
	"""
	The method returns a list of an organized adoption_center such that the scores for each AdoptionCenter to the Adopter will be ordered from highest score to lowest score.
	"""
	items = {}
	for center in list_of_adoption_centers:
		items[center.get_name()] = adopter.get_score(center)
	backwords = sorted(items, key=lambda x: items[x])
	return list(reversed(backwords))

def get_adopters_for_advertisement(adoption_center, list_of_adopters, n):
	"""
	The function returns a list of the top n scoring Adopters from list_of_adopters (in numerical order of score)
	"""
	items = {}
	for adoptor in list_of_adopters:
		items[adoptor.get_name()] = adoptor.get_score(adoption_center)
	listing =list(reversed(sorted(items, key=lambda x: items[x])))
	final = []
	for item in listing:
		if n > 0:
			final.append(item)
			n -= 1
		else:
			break
	return final
