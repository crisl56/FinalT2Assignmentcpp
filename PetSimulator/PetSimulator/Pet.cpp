#pragma once
#include "Pet.h"
#include "UIManager.h"
#include "PetDialogue.h"
#include "RandomChance.h"

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

// TODO: all of this lmao
void Pet::NamePet()
{
	// ask for a pet name -> uimanager

	// set name to this new pet name

	// see if pet likes it

	//if () {

	//}
}

void Pet::FeedPet()
{
}

void Pet::HydratePet()
{
}

void Pet::CleanPet()
{
}

void Pet::RecreationPet()
{
}

void Pet::TrainPet()
{
}

void Pet::RestPet()
{
	// UI manage somehow yea
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
		return true;
	}

	return false;
}

void Pet::CheckHealth()
{
	const int unHealthStatsThreshold = 20;
	const int HealthDecrease = 10;

	if (_hunger >= unHealthStatsThreshold || _thirstiness >= unHealthStatsThreshold) {
		return;
	}

	// Play Message here for unhealthy pet
	UIManager::GetInstance()->ShowPetActionDialogue(PetDialogue::unHealthyDialogue);

	_health -= HealthDecrease;


}

// Check if clean and if not decreases health
void Pet::CheckCleanliness()
{

}


void Pet::SetSpeed(int newSpeed)
{
	_speed = newSpeed;
}

