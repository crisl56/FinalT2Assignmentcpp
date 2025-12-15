#pragma once
#include "Utils.h"
#include "InputAction.h"

class Race;
class Pet;

// Singleton
class UIManager
{
public:
	static std::shared_ptr<UIManager> GetInstance();

	// UI Showing functions
	void ShowTitle();
	void ShowPetStats(const Pet& _pet);
	void ShowGameOptions(const Pet& _pet);
	void ShowRaceOptions();
	void ShowRaceResults(const Race& race);
	void ShowPetDeadOptions(const Pet& _pet);

	// UI Input helpers
	string AskString(const string& message);
	InputType AskMenuGameOption(const string& message, int min, int max);
	int AskInt(const string& message, int min, int max);
	void ClearConsole();
	void PressToContinue();

	// Pet Stuff
	string AskPetName();
	void ShowPetActionDialogue(const std::vector<string>& dialogue);

private:
	UIManager();
	static std::shared_ptr<UIManager> sInstance;
};

