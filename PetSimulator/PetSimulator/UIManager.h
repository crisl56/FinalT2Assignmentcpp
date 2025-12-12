#pragma once
#include "Utils.h"

class Race;
class Pet;

class UIManager
{
public:
	void ShowTitle();
	void ShowPetStats(const Pet& _pet);
	void ShowGameOptions(const Pet& _pet);
	void ShowRaceOptions();
	void ShowRaceResults(const Race& race);
	void ShowPetDeadOptions(const Pet& _pet);

	string AskString(const string& message);
	int AskInt(const string& message, int min, int max);

	void ClearConsole();
	void PressToContinue();
private:
};

