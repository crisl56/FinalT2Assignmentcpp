#pragma once
#include <memory>
#include <unordered_map>
#include "InputAction.h"
#include <functional>

class Pet;
class UIManager;
class PetFactory;
class Race;

using MenuActionSignature = std::function<void()>;

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void Run();
	void InitGame();
	void MainMenuLoop();

private:
	bool _isRunning;
	std::shared_ptr<UIManager> _uiManagerPointer;
	std::unique_ptr<Pet> _petPlayerPointer;
	std::unique_ptr<Race> _race;

	std::unordered_map<InputType, MenuActionSignature> _InputFunctionMap;

	void CheckPetDeath();
	void HandleRaceOption();
};

