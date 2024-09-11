#pragma once
#include "human.h"

class Player : public Human
{
public:
	Player();
	void Tick(float deltaTime) override;
};
