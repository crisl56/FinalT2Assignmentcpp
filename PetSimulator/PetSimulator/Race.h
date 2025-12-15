#pragma once
#include <list>
#include <vector>
#include <random>
#include <memory>

class Pet;
class PetFactory;

// Different difficulty types
enum class Difficulty
{
	Easy = 1,
	Medium = 2,
	Hard = 3,
	Impossible = 4,
};

class Race
{
public:

	// Data for each racer
	struct Result 
	{
		const Pet* pet;
		int position;
		float score;
		bool isPlayer;
	};

	// Constructors and Destructor
	Race() = delete;
	Race(int numberCompetitors, Difficulty difficulty, Pet& petPlayer);
	~Race() {};

	// Race process
	void StartRace();

	Difficulty GetDifficulty() const;

	// Returns the results for each player
	const std::vector<Result>& GetResults() const;

	// Returns a flag to know if player won
	bool DidPlayerWin() const;
private:

	// Race features
	int distance;
	int _numberCompetitors;
	Difficulty _currentRaceDifficulty;

	// Racers 
	std::list<std::unique_ptr<Pet>> _petCompetitorsList;

	// Reference to the pet player
	Pet& _playerPet;

	// Results
	std::vector<Result> _results;

	// Player win flag
	bool _playerWon = false;

	void GenerateCompetitors();

	// Helper that calculates the race time for each racer
	float CalculateTimeScore(int speed);

	int GetRandomInt(int min, int max);
};

