#include "Pet.h"

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
void Pet::NamePet(string newPetName)
{
	// set name to this new pet name


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
}
