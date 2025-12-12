#pragma once
#include <memory>
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

	void Run();
	void InitGame();
	void MainMenuLoop();

private:
	bool _isRunning;
	std::unique_ptr<UIManager> _uiManagerPointer;
	std::unique_ptr<Pet> _petPlayerPointer;
	std::unique_ptr<Race> _race;

	MenuActionSignature _menuAction;

	void CheckPetDeath();
	void HandleRaceOption();
};

