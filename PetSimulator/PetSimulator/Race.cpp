#include "Race.h"
#include "Pet.h"
#include "PetFactory.h"
#include "Utils.h"
#include <algorithm>

Race::Race(int numberCompetitors, Difficulty difficulty, Pet& petPlayer) :
	_numberCompetitors(numberCompetitors),
	_currentRaceDifficulty(difficulty),
	_playerPet(petPlayer)
{
	GenerateCompetitors();
}

void Race::StartRace()
{
    _results.clear();
    _playerWon = false;

    switch (_currentRaceDifficulty)
    {
        case Difficulty::Easy:
            distance = 100;
            break;
        case Difficulty::Medium:
            distance = 250;
            break;
        case Difficulty::Hard:
            distance = 400;
            break;
        case Difficulty::Impossible:
            distance = 1000;
            break;
    }

    _results.push_back({ &_playerPet, 0, CalculateTimeScore(_playerPet.GetSpeed()), true});

    for (auto& rivalPointer : _petCompetitorsList)
    {
        Pet& rival = *rivalPointer;
        _results.push_back({ &rival, 0, CalculateTimeScore(rival.GetSpeed()), false });
    }

    std::sort(_results.begin(), _results.end(), [](const Result& a, const Result& b)
    {
        return a.score < b.score;
    });

    for (int i = 0; i < (int)_results.size(); ++i)
    {
        _results[i].position = i + 1;
    }

    _playerWon = (_results.size() > 0 && _results[0].isPlayer);
}

Difficulty Race::GetDifficulty() const
{
	return _currentRaceDifficulty;
}

const std::vector<Race::Result>& Race::GetResults() const
{
    return _results;
}

bool Race::DidPlayerWin() const
{
	return _playerWon;
}

void Race::GenerateCompetitors()
{
    if (_numberCompetitors < 0)
    {
        _numberCompetitors = 0;
    }

    _petCompetitorsList.clear();

    for (int i = 0; i < _numberCompetitors; ++i)
    {
        string rivalName = "Racer " + std::to_string(i + 1);
        int rivalSpeed = GetRandomInt(5, 8);

        // Note why can't you just change the speed when you create the pet?
        // I think unique ptr is bad here unless you store it somewhere
        std::unique_ptr<Pet> rivalPointer = PetFactory::GetInstance()->CreatePet(rivalName, rivalSpeed);

        // You could you totally do an unordered map
        switch (_currentRaceDifficulty)
        {
            case Difficulty::Easy:
                rivalPointer->SetSpeed(rivalPointer->GetSpeed() + 1);
                break;
            case Difficulty::Medium:
                rivalPointer->SetSpeed(rivalPointer->GetSpeed() + 2);
                break;
            case Difficulty::Hard:
                rivalPointer->SetSpeed(rivalPointer->GetSpeed() + 3);
                break;
            case Difficulty::Impossible:
                rivalPointer->SetSpeed(rivalPointer->GetSpeed() + 5);
                break;
        }

        _petCompetitorsList.push_back(std::move(rivalPointer));
    }
}

float Race::CalculateTimeScore(int speed)
{
    if (speed <= 0)
    {
        speed = 1;
    }

    float timeScore = (float)distance / (float)speed;
    return timeScore;
}

int Race::GetRandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}
