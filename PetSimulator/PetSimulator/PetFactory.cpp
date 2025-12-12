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

std::unique_ptr<Pet> PetFactory::CreatePet(string Name)
{
	return CreatePet(Name, 0);
}

std::unique_ptr<Pet> PetFactory::CreatePet(string Name, int Speed)
{
	Pet* newPet = new Pet(Name, Speed);

	PetVector.push_back(newPet);

	// Not sure if this works
	return std::move(std::make_unique<Pet>(*newPet));
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
