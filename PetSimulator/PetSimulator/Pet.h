#pragma once
#include "Utils.h"
#include "PetFactory.h"

class Pet;
class PetFactory;

class Pet
{
	friend PetFactory;
public:
	Pet() = delete;

	// Enums for later
	// Effects health of pet
	enum Cleanliness {
		Dirty = 1,
		Clean,
		Sparkling
	};

	// Effects how effective some activities are
	enum  Mood {
		Bad = 1,
		Normal,
		Excellent,
	};


	// Player Actions
	void NamePet();
	void FeedPet();
	void HydratePet();
	void CleanPet();
	void RecreationPet();
	void TrainPet();
	void RestPet();

	// Checks
	bool CheckDead();
	bool CheckMood();
	void CheckHealth();
	void CheckCleanliness();
	
	// Getters
	string GetName() const;
	int GetEnergy() const;
	int GetHealth() const;
	int GetHunger() const;
	int GetThirstiness() const;
	int GetSpeed() const;
	Mood GetMood() const;
	Cleanliness GetCleanState() const;


	// Setters
	void SetSpeed(int newSpeed);


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
	Cleanliness _cleanPetState;


	Mood _currentMood;
	int _speed;
	

};

