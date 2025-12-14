#pragma once
#include <random>

// Honeslty not sure if this is a good idea but since its just doing math I hope it is fine.
static class RandomChance {
public:
	static bool Probability(int percentage ) {
		std::random_device rd;

		std::mt19937 engine(rd());
		
		std::uniform_int_distribution<int> dist(1, 100);

		return dist(engine) <= percentage;
	}
};