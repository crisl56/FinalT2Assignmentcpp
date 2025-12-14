#include "GameLoop.h"
#include "Utils.h"
#include "UIManager.h"
#include "PetFactory.h"
#include "Pet.h"
#include "Race.h"

GameLoop::GameLoop() : 
	_isRunning(true),
	_uiManagerPointer(UIManager::GetInstance()),
	_petPlayerPointer(nullptr),
	_race(nullptr)
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

	_InputFunctionMap ={ //{ {InputType::Input_Key_1, std::bind( & Pet::FeedPet, _petPlayerPointer.get())}, {InputType::Input_Key_1, nullptr}};
	{InputType::Input_Key_1, std::bind(&Pet::FeedPet, _petPlayerPointer.get())},
	{InputType::Input_Key_2, std::bind(&Pet::HydratePet, _petPlayerPointer.get())},
	{InputType::Input_Key_3, std::bind(&Pet::CleanPet, _petPlayerPointer.get())},
	{InputType::Input_Key_4, std::bind(&Pet::RecreationPet, _petPlayerPointer.get())},
	{InputType::Input_Key_5, std::bind(&Pet::TrainPet, _petPlayerPointer.get())},
	{InputType::Input_Key_6, std::bind(&Pet::RestPet, _petPlayerPointer.get())},
	{InputType::Input_Key_7, std::bind(&Pet::NamePet, _petPlayerPointer.get())}, 
	{InputType::Input_Key_8, std::bind(&GameLoop::HandleRaceOption, this)},
	{InputType::Input_Key_9, nullptr},
	{InputType::Input_Key_None, nullptr} };
	MainMenuLoop();
}

void GameLoop::MainMenuLoop()
{
	while (_isRunning)
	{
		_uiManagerPointer->ClearConsole();

		_uiManagerPointer->ShowPetStats(*_petPlayerPointer);
		_uiManagerPointer->ShowGameOptions(*_petPlayerPointer);

		InputType inputMenu = _uiManagerPointer->AskInt("What would you like to do today?", 1, 9);

		if (inputMenu == InputType::Input_Key_9)
		{
			_isRunning = false;
			continue;
		}
		else if (inputMenu != InputType::Input_Key_None)
		{
			_InputFunctionMap[inputMenu];
		}

		_uiManagerPointer->ClearConsole();

		_petPlayerPointer->CheckCleanliness();
		_petPlayerPointer->CheckHealth();

		CheckPetDeath();
	}
}

void GameLoop::CheckPetDeath()
{
	if (_petPlayerPointer->CheckDead() || _petPlayerPointer->CheckMood())
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
