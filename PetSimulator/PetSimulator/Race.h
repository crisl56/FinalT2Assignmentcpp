#pragma once
#include <list>
#include <vector>
#include <random>
#include <memory>

class Pet;
class PetFactory;

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

	struct Result 
	{
		const Pet* pet;
		int position;
		float score;
		bool isPlayer;
	};

	Race() = delete;
	Race(int numberCompetitors, Difficulty difficulty, Pet& petPlayer);
	~Race() {};

	void StartRace();

	Difficulty GetDifficulty() const;
	const std::vector<Result>& GetResults() const;
	bool DidPlayerWin() const;
private:

	int distance;
	int _numberCompetitors;
	Difficulty _currentRaceDifficulty;

	std::list<std::unique_ptr<Pet>> _petCompetitorsList;
	Pet& _playerPet;
	std::vector<Result> _results;
	bool _playerWon = false;

	void GenerateCompetitors();
	int CalculateTimeScore(int speed);

	int GetRandomInt(int min, int max);
};

