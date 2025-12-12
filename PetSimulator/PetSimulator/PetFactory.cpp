#include "PetFactory.h"
#include "Chance.h"

PetFactory::~PetFactory()
{
	// Deletes all pets stored once this factory is destroyed.
	for (Pet* currentPetIteration : PetVector) {
		delete currentPetIteration;
		currentPetIteration = nullptr;
	}

	// Delete self
	delete sInstance;
	sInstance = nullptr;
}

PetFactory* PetFactory::sInstance = nullptr;

PetFactory* PetFactory::GetInstance()
{
	if (sInstance == nullptr) {
		sInstance = new PetFactory();
	}

	return sInstance;
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
