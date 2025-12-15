#pragma once
#include <memory>
#include <unordered_map>
#include "InputAction.h"
#include <functional>

// Forward Declaration
class Pet;
class UIManager;
class PetFactory;
class Race;

// Menu Signature
using MenuActionSignature = std::function<void()>;

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	// Running game functions
	void Run();
	void InitGame();
	void MainMenuLoop();

	// Assigns the input map to the current pet options
	void BuildInputMap();

private:
	// Game running flag
	bool _isRunning;

	// Game Loop as the owner of the following unique pointers/shared
	std::shared_ptr<UIManager> _uiManagerPointer;
	std::unique_ptr<Pet> _petPlayerPointer;
	std::unique_ptr<Race> _race;

	// Unordered map for menu game options
	std::unordered_map<InputType, MenuActionSignature> _InputFunctionMap;

	// Pet status checking
	void CheckPetDeath();

	void HandleRaceOption();
};

