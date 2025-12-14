#pragma once
#include "Utils.h"
#include <vector>
#include "Pet.h"

class Pet;

class PetFactory {
public:
	~PetFactory();

	static PetFactory* GetInstance();

	std::unique_ptr<Pet> CreatePet(string Name);
	std::unique_ptr<Pet> CreatePet(string Name, int Speed);
	
	// Getter and setters
	Pet* GetPet(int index);

private:
	static PetFactory* sInstance;

	// NOTE: I am assuming that the first pet will always bet the player pet.
	std::vector<Pet*> PetVector;
};