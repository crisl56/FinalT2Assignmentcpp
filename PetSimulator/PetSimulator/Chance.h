#pragma once
#include "Utils.h"
#include <memory>

class Chance
{
public:
	Chance* GetInstance();

	// acts like inMaxnum inside 
	bool Roll(int maxNum, int inMaxNum);
	bool Roll(float probability);

private:
	Chance();
	~Chance();

	static Chance* sInstance;
};