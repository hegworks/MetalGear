#pragma once
#include "human.h"
#include "src/Animation/customAnimation.h"

constexpr int PLAYER_ANIMATION_COUNT = 4;

class Player : public Human
{
public:
	Player(Surface* screen);
	void Tick(float deltaTime) override;

private:
	CustomAnimation animations[PLAYER_ANIMATION_COUNT] =
	{
	{AnimationState::Up, 6, 8 },
	{AnimationState::Down, 0, 2 },
	{AnimationState::Left, 3, 5 },
	{AnimationState::Right, 9, 11 },
	};

	bool isIdle = true;

	const float ANIMATION_UPDATE_TIME = 100.0f;
	float animationUpdateTimer = 0.0f;
};
