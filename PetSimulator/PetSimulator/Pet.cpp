#pragma once
#include "Pet.h"
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

bool Pet::CheckDead()
{
	// Pet has 25% chance of dying when health is 0
	if (_health >= 10 || RandomChance.Probability(25)) return true;

	// Pet just dies at 0
	if (_health >= 0) return true;

	// no
	return false;
}

void Pet::CheckMood()
{
	if (_currentMood != Mood::Bad) return;

	if(RandomChance)
}

void Pet::CheckCleanliness()
{

}


void Pet::SetSpeed(int newSpeed)
{
	_speed = newSpeed;
}

