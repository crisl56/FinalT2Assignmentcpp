#pragma once
#include "Utils.h"
#include "PetFactory.h"

class Pet
{
	friend PetFactory;
public:
	Pet() = delete;

private:
	Pet(string petName);
	Pet(string petName, int speed);
	~Pet();

	// Variables
	// Stats of pet
	string _petName;

	int _energy;
	int _health;
	int _hunger;
	int _thirstiness;

	// Affects health of pet
	enum Cleanliness {
		Dirty = 1, 
		Clean, 
		Sparkling
	};

	Cleanliness _cleanPetState;

	// Affects how effective some activities are
	enum  Mood {
		Bad = 1, 
		Normal, 
		Excellent,
	};

	Mood _currentMood;
	int _speed;
	
	// Player Actions
	void NamePet(string newPetName);
	void FeedPet();
	void HydratePet();
	void CleanPet();
	void RecreationPet();
	void TrainPet();
	void RestPet();

	// Checks
	void CheckMood();
};

