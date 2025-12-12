#include "GameLoop.h"
#include "Utils.h"
#include "UIManager.h"
#include "PetFactory.h"
#include "Pet.h"
#include "Race.h"

GameLoop::GameLoop() : 
	_isRunning(true),
	_uiManagerPointer(std::make_unique<UIManager>()),
	_petPlayerPointer(nullptr),
	_race(nullptr),
	_menuAction(nullptr)
{
}

void GameLoop::Run()
{
	InitGame();
}

void GameLoop::InitGame()
{
	_uiManagerPointer->ShowTitle();
	string inputName = _uiManagerPointer->AskString("Enter your pet's name");
	_petPlayerPointer = PetFactory::GetInstance()->CreatePet(inputName);
	MainMenuLoop();
}

void GameLoop::MainMenuLoop()
{
	while (_isRunning)
	{
		_uiManagerPointer->ClearConsole();

		_uiManagerPointer->ShowPetStats(*_petPlayerPointer);
		_uiManagerPointer->ShowGameOptions(*_petPlayerPointer);

		int inputMenu = _uiManagerPointer->AskInt("What would you like to do today?", 1, 9);

		_menuAction = nullptr;

		switch (inputMenu)
		{
			case 1:
				_menuAction = std::bind(&Pet::FeedPet, _petPlayerPointer.get());
				break;
			case 2:
				_menuAction = std::bind(&Pet::HydratePet, _petPlayerPointer.get());
				break;
			case 3:
				_menuAction = std::bind(&Pet::CleanPet, _petPlayerPointer.get());
				break;
			case 4:
				_menuAction = std::bind(&Pet::SpendTimeWithPet, _petPlayerPointer.get());
				break;
			case 5:
				_menuAction = std::bind(&Pet::TrainPet, _petPlayerPointer.get());
				break;
			case 6:
				_menuAction = std::bind(&Pet::Rest, _petPlayerPointer.get());
				break;
			case 7:
				_menuAction = std::bind(&Pet::NamePet, _petPlayerPointer.get());
				break;
			case 8:
				_menuAction = std::bind(&GameLoop::HandleRaceOption, this);
				break;
			case 9:
				_isRunning = false;
				continue;
			default:
				break;
		}

		if (_menuAction)
		{
			_menuAction();
		}

		_uiManagerPointer->ClearConsole();

		CheckPetDeath();
	}
}

void GameLoop::CheckPetDeath()
{
	if (_petPlayerPointer->GetIsDead())
	{
		_uiManagerPointer->ShowPetDeadOptions(*_petPlayerPointer);

		int input = _uiManagerPointer->AskInt("", 1, 2);

		if (input == 1)
		{
			string newName = _uiManagerPointer->AskString("Enter your pet's name");
			_petPlayerPointer = PetFactory::GetInstance()->CreatePet(newName);
		}
		else if (input == 2)
		{
			_isRunning = false;
		}
	}
}

void GameLoop::HandleRaceOption()
{
	_uiManagerPointer->ShowRaceOptions();
	int difficultyInput = _uiManagerPointer->AskInt("Choose difficulty", 1, 4);

	Difficulty difficulty = static_cast<Difficulty>(difficultyInput);

	_race = std::make_unique<Race>(3, difficulty, *_petPlayerPointer);
	_race->StartRace();
	_uiManagerPointer->ShowRaceResults(*_race);
	_uiManagerPointer->PressToContinue();
}
