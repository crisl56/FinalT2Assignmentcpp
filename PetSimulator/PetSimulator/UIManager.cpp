#include <vector>
#include "Utils.h"
#include "UIManager.h"
#include "Pet.h"
#include "Race.h"

void UIManager::ShowTitle()
{
	LOG_LN(
		"===================================\n" <<
		"PET SIMULATOR					    \n" <<
		"By Cris and Yeison					\n" <<
		"===================================\n" <<
		"Let's start creating a new Pet for you!\n"
	);
}

void UIManager::ShowPetStats(const Pet& _pet)
{
	LOG_LN("\n=================================== \n" << 
		   _pet.GetName() << "'s Stats\n" <<
	         "===================================" <<
			 "Energy      :" << _pet.GetEnergy()     << "\n" <<
			 "Dirtiness   :" << _pet.GetDirtiness()  << "\n" <<
			 "Health      :" << _pet.GetHealth()     << "\n" <<
			 "Hunger      :" << _pet.GetHunger()     << "\n" <<
			 "Thirstiness :" << _pet.GetThirstiness() << "\n" <<
			 "Mood        :" << _pet.GetMood()       << "\n" <<
			 "Speed       :" << _pet.GetSpeed()      << "\n" <<
		     "===================================\n"
	);
}

void UIManager::ShowGameOptions(const Pet& _pet)
{
	LOG_LN("\n=================================== \n" <<
			"----------- Pet Options -----------  \n" <<
			"===================================    " <<
			"1. Feed     " << _pet.GetName() << "\n" <<
			"2. Hydrate  " << _pet.GetName() << "\n" <<
			"3. Clean    " << _pet.GetName() << "\n" <<
			"4. Spend time with " << _pet.GetName() << "\n" <<
			"5. Train "    << _pet.GetName() << "\n" <<
			"6. Rest "     << _pet.GetName() << "\n" <<
			"7. Rename "   << _pet.GetName() << "\n" <<
			"8. Race "     << _pet.GetName() << "\n" <<
			"9. Exit "						  << "\n" <<
			"===================================\n"
	);
}

void UIManager::ShowRaceOptions()
{
	LOG_LN(
		"===================================\n" <<
		"----------- Race Options ----------\n" <<
		"===================================\n" <<
		"1. Easy							\n" <<
		"2. Medium							\n" <<
		"3. Hard							\n" <<
		"4. Impossible						\n" <<
		"===================================" << "\n"
	);
}

void UIManager::ShowRaceResults(const Race& race)
{
	LOG_LN(
		"\n===================================\n"
		"----------- Race Results ----------\n"
		"===================================\n"
	);

	const auto& results = race.GetResults();

	for (const auto& r : results)
	{
		LOG_LN(
			r.position << ". "
			<< r.pet->GetName()
			<< (r.isPlayer ? " (You)" : "")
			<< " | Time: " << r.score <<
			"===================================\n"
		);
	}

	if (race.DidPlayerWin())
	{
		LOG_LN("You won the race");
	}
	else
	{
		LOG_LN("You lost the race");
	}
	LOG_LN("===================================\n");
}

void UIManager::ShowPetDeadOptions(const Pet& _pet)
{
	LOG_LN(
		"===================================\n" <<
		"------- Your pet is dead :( -------\n" <<
		"===================================\n" <<
		"-- Would you like to play again? --\n" <<
		"===================================\n" <<
		"1. Yes								\n" <<
		"2. No							    \n" <<
		"===================================" << "\n"
	);
}

void UIManager::ClearConsole()
{
	std::cout << "\033[2J\033[1;1H";
}


string UIManager::AskString(const string& message)
{
	string input;

	while (true)
	{
		LOG_LN(message);
		std::getline(std::cin, input);

		if (!input.empty())
		{
			return input;
		}

		LOG_LN("Invalid input, try again.\n");
	}
}

InputType UIManager::AskInt(const string& message, int min, int max)
{
	string input;
	int value = 0;
	InputAction CurrentInputAction;
	std::cin >> (CurrentInputAction);
	return CurrentInputAction.mInputKey;
	/*while (true)
	{
		LOG_LN(message);
		std::getline(std::cin, input);

		try
		{
			value = std::stoi(input);

			if (value >= min && value <= max)
			{
				return value;
			}
			LOG_LN("Number out of range, try again.\n");
		}
		catch (...)
		{
			LOG_LN("Invalid number, try again.\n");
		}
	}*/
}

void UIManager::PressToContinue()
{
	LOG("Press anything to continue...");
	string input;
	std::getline(std::cin, input);
}

