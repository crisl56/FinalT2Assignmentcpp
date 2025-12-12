#include "PetFactory.h"

PetFactory::~PetFactory()
{
	// Deletes all pets stored once this factory is destroyed.
	for (Pet* currentPetIteration : PetVector) {
		delete currentPetIteration;
		currentPetIteration = nullptr;
	}
}

std::unique_ptr<PetFactory> PetFactory::GetInstance()
{
	return std::move(sInstance);
}

void PetFactory::CreatePet(string Name)
{
	CreatePet(Name, 0);
}

void PetFactory::CreatePet(string Name, int Speed)
{
	Pet* newPet = new Pet(Name, Speed);

	PetVector.push_back(newPet);
}

Pet* PetFactory::GetPet(int index)
{
	// Check if valid
	if (PetVector.size() < index) {
		// Maybe we could throw an assertion here
		return nullptr;
	}

	return PetVector[index];
}
