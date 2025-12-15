#pragma once
#include <algorithm>
#include "Pet.h"
#include "UIManager.h"
#include "PetDialogue.h"
#include "RandomChance.h"

#define UIManagerPtr UIManager::GetInstance()
#define ShowActions(X) UIManager::GetInstance()->ShowPetActionDialogue(X);

// This constructer just does the other constructor but has speed defaulted to 0
Pet::Pet(string petName) : Pet(petName, 0) {}

Pet::Pet(string petName, int speed)
    :_petName(petName)
	,_speed(speed)
	,_energy(100)
	,_health(100)
	,_hunger(100)
	,_thirstiness(100)
	,_cleanPetState(Cleanliness::Clean)
	,_currentMood(Mood::Normal)
{
}

Pet::~Pet(){
	// Don't know yet tbh
}

void Pet::DecreaseEnergy()
{
	int randomIndex = (rand() % 3);

	int newEnergy = _energy - _actionEffectiveness[randomIndex];
	_energy = std::max(0, std::min(100, newEnergy));
}

// TODO: all of this lmao
void Pet::NamePet()
{
	// ask for a pet name -> uimanager
	string newPetName = UIManagerPtr->AskPetName();

	// set name to this new pet name
	_petName = newPetName;

	// see if pet likes it
	const int DislikeProbability = 30;

	if (RandomChance::Probability(DislikeProbability)) {
		ShowActions(PetDialogue::nameSadDialogue);

		if (_currentMood != Mood::Bad) {
			_currentMood = static_cast<Mood>(static_cast<int>(_currentMood) - 1);
		}
	}
	else {
		ShowActions(PetDialogue::nameHappyDialogue);

		if (_currentMood != Mood::Excellent) {
			_currentMood = static_cast<Mood>(static_cast<int>(_currentMood) + 1);
		}
	}
}

void Pet::FeedPet()
{
	// Use energy as a point of failure 
	if (!(RandomChance::Probability(_energy))) {
		LOG_LN("FAIL!!!");
		ShowActions(PetDialogue::failDialogue);

		int randomIndex = (rand() % 3);

		int newHunger = _hunger - _actionEffectiveness[randomIndex];
		_hunger = std::max(0, std::min(100, newHunger));

		return;
	}

	int randomIndex = (rand() % 3);

	int newHunger = _hunger + _actionEffectiveness[randomIndex];
	_hunger = std::max(0, std::min(100, newHunger));

	ShowActions(PetDialogue::feedDialogue);
	DecreaseEnergy();
}

void Pet::HydratePet()
{
	if (!(RandomChance::Probability(_energy))) {
		LOG_LN("FAIL!!!");
		ShowActions(PetDialogue::failDialogue);

		int randomIndex = (rand() % 3);

		int newThirstiness = _thirstiness - _actionEffectiveness[randomIndex];
		_thirstiness = std::max(0, std::min(100, newThirstiness));

		return;
	}

	int randomIndex = (rand() % 3);

	int newThirstiness = _thirstiness + _actionEffectiveness[randomIndex];
	_thirstiness = std::max(0, std::min(100, newThirstiness));

	ShowActions(PetDialogue::hydrateDialogue);

	DecreaseEnergy();
}

void Pet::CleanPet()
{
	if (!(RandomChance::Probability(_energy))) {
		LOG_LN("FAIL!!!");
		ShowActions(PetDialogue::failDialogue);

		int newCleanState = static_cast<int>(_cleanPetState) - 1;
		_cleanPetState = static_cast<Cleanliness>(std::max(1, std::min(3, newCleanState)));

		return;
	}

	ShowActions(PetDialogue::cleanDialogue);

	int newCleanState = static_cast<int>(_cleanPetState) + 1;
	_cleanPetState = static_cast<Cleanliness>(std::max(1, std::min(3, newCleanState)));

	DecreaseEnergy();
}

void Pet::RecreationPet()
{
	if (!(RandomChance::Probability(_energy))) {
		LOG_LN("FAIL!!!");
		ShowActions(PetDialogue::failDialogue);
		 
		int newMood = static_cast<int>(_currentMood) - 1;
		_currentMood = static_cast<Mood>(std::max(1, std::min(3, newMood)));

		return;
	}

	ShowActions(PetDialogue::recreationDialogue);

	int newMood = static_cast<int>(_currentMood) + 1;
	_currentMood = static_cast<Mood>(std::max(1, std::min(3, newMood)));

	DecreaseEnergy();
}

void Pet::TrainPet()
{
	// Decrease stats for trainning
	int randomIndex = (rand() % 3);
	
	int newHunger = _hunger - _actionEffectiveness[randomIndex];
	_hunger = std::max(0, std::min(100, newHunger));

	int newThirstiness = _thirstiness - _actionEffectiveness[randomIndex];
	_thirstiness = std::max(0, std::min(100, newThirstiness));

	// Gets dirty
	if (RandomChance::Probability(25)) {
		int newCleanState = static_cast<int>(_cleanPetState) - 1;
		_cleanPetState = static_cast<Cleanliness>(std::max(1, std::min(3, newCleanState)));
	}

	if (!(RandomChance::Probability(_energy))) {
		LOG_LN("FAIL!!!");
		ShowActions(PetDialogue::failDialogue);

		int randomIndex = (rand() % 3);

		int newMood = static_cast<int>(_currentMood) - 1;
		_currentMood = static_cast<Mood>(std::max(1, std::min(3, newMood)));

		return;
	}

	// Current mood multiples the speed increase
	int newSpeed = _speed + _actionEffectiveness[randomIndex] * static_cast<int>(_currentMood);;
	_speed = std::max(0, std::min(100, newSpeed));

	ShowActions(PetDialogue::trainDialogue);
	DecreaseEnergy();
}

void Pet::RestPet()
{
	const int resetMultiplier = 2;

	int randomIndex = (rand() % 3);

	int newEnergy = _energy + _actionEffectiveness[randomIndex] * resetMultiplier	;
	_energy = std::max(0, std::min(100, newEnergy));

	ShowActions(PetDialogue::restDialogue);

}

// Returns true if dead false otherwise
bool Pet::CheckDead()
{
	const int DeathProbability = 25;

	// Pet has 25% chance of dying when health is 0
	if (_health == 0 && RandomChance::Probability(DeathProbability)) return true;

	// Pet just dies at 0
	if (_health >= 0) return true;

	// not dead
	return false;
}

// Returns true if ranaway false otherwise
bool Pet::CheckMood()
{
	const int RunawayProbability = 25;

	if (_currentMood != Mood::Bad) return false;

	if (RandomChance::Probability(RunawayProbability)) {
		ShowActions(PetDialogue::moodDialogue);

		return true;
	}

	return false;
}

// Updates health stat accordingly to the hunger and thirstiness
void Pet::CheckHealth()
{
	const int unHealthStatsThreshold = 20;
	const int HealthDecrease = 10;

	if (_hunger >= unHealthStatsThreshold || _thirstiness >= unHealthStatsThreshold) {
		return;
	}

	// Play Message here for unhealthy pet
	ShowActions(PetDialogue::unHealthyDialogue);

	_health -= HealthDecrease;
}

// Check if clean and if not decreases health
void Pet::CheckCleanliness()
{
	const int healthDownProbability = 25;
	const int HealthDecrease = 10;

	if (_cleanPetState != Cleanliness::Dirty) return;

	if (RandomChance::Probability(healthDownProbability)) {
		_health -= HealthDecrease;
	}
}

string Pet::GetName() const
{
	return _petName;
}

int Pet::GetEnergy() const
{
	return _energy;
}

int Pet::GetHealth() const
{
	return _health;
}

int Pet::GetHunger() const
{
	return _hunger;
}

int Pet::GetThirstiness() const
{
	return _thirstiness;
}

int Pet::GetSpeed() const // I created the getspeed function since there wasn't in your previous commit
{
	return _speed;
}

Pet::Mood Pet::GetMood() const
{
	return _currentMood;
}

Pet::Cleanliness Pet::GetCleanState() const
{
	return _cleanPetState;
}


void Pet::SetSpeed(int newSpeed)
{
	_speed = newSpeed;
}

