#pragma once
#include "human.h"

class Player : public Human
{
public:
	Player(Surface* screen);
	void Tick(float deltaTime) override;
};
