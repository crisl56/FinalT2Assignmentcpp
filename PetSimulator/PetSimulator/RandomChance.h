#pragma once
#include <random>

// Honeslty not sure if this is a good idea but since its just doing math I hope it is fine.
class RandomChance { // Here
public:

	// Returns true if it hits that percentage
	// Returns false if it doesn't
	static bool Probability(int percentage ) {
		std::random_device rd;

		std::mt19937 engine(rd());
		
		std::uniform_int_distribution<int> dist(1, 100);

		return dist(engine) <= percentage;
	}
};