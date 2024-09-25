#pragma once
#include <ctime>

class Rng
{
public:
	Rng()
	{
		ResetSeed();
	}

	int BetweenInclusive(int a, int b)
	{
		// Ensure that a <= b for the formula to work correctly
		if(a > b)
		{
			int temp = a;
			a = b;
			b = temp;
		}

		// Generate a random number between a and b, inclusive
		return a + rand() % (b - a + 1);
	}

	void ResetSeed()
	{
		srand(static_cast<int>(time(0)));
	}
};