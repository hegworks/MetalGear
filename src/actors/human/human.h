#pragma once
#include "src/animation/animationState.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/tile/levelMap/levelMaps.h"

class Human
{
public:
	Human(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage);
	~Human();

	void Draw() const;
	virtual void DrawColliders() const {}
	virtual void Move(int2 direction) {}
	virtual void Tick(float deltaTime) {}

protected:
	Surface* screen = nullptr;
	LevelMaps* levelMaps = nullptr;
	SpriteStorage* spriteStorage = nullptr;

	AnimationState currentAnimationState = AnimationState::Down;
	AnimationState lastAnimationState = AnimationState::Down;

	Sprite* sprite = nullptr;

	float2 position;
	float speed;
	int animationFrame;
};
