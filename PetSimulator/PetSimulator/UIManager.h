#pragma once
#include "Utils.h"
#include "InputAction.h"

class Race;
class Pet;

class UIManager
{
public:
	// shared pointer singlton
	// - note: i don't think we need a factory as we only really need 1 UI manager
	static std::shared_ptr<UIManager> GetInstance();

	void ShowTitle();
	void ShowPetStats(const Pet& _pet);
	void ShowGameOptions(const Pet& _pet);
	void ShowRaceOptions();
	void ShowRaceResults(const Race& race);
	void ShowPetDeadOptions(const Pet& _pet);

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

