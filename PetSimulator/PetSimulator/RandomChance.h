#pragma once
#include <random>

static class RandomChance {
	bool Probability(const int* percentage ) {
		std::random_device rd;

		std::mt19937 engine(rd());
		
		std::uniform_int_distribution<int> dist(1, 100);

		return dist(engine) <= *percentage;
	}
};