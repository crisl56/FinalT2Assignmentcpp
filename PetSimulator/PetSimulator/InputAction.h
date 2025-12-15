#pragma once
#include <iostream>
#include <unordered_map>
#include <algorithm>

enum class InputType
{
	Input_Key_1,
	Input_Key_2,
	Input_Key_3,
	Input_Key_4,
	Input_Key_5,
	Input_Key_6,
	Input_Key_7,
	Input_Key_8,
	Input_Key_9,
	Input_Key_None
};

class InputAction
{

public:

	InputType mInputKey = InputType::Input_Key_None;
	friend std::istream& operator>>(std::istream& InputStream, InputAction& Input)
	{
		int InputInteger = 0;
		InputStream >> InputInteger;

		auto FoundIt = InputAction::sInputMap.find(InputInteger);
		if (FoundIt != InputAction::sInputMap.end())
		{
			Input.mInputKey = FoundIt->second;
		}
		else
		{
			Input.mInputKey = InputType::Input_Key_None;
		}

		return InputStream;
	}

private:

	static std::unordered_map<int, InputType>  sInputMap;
};
