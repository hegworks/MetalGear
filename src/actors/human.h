#pragma once
#include "src/animation/animationState.h"
#include "src/tile/levelMap/levelMaps.h"

class Human
{
public:
	Human(Surface* screen, LevelMaps* levelMaps);
	~Human();
	char* spriteAddress;
	int graphicFrames;
	Sprite* graphic;
	float2 position;
	float speed;
	int animationFrame;

	void Draw() const;
	virtual void Move(int2 direction);
	virtual void Tick(float deltaTime);

protected:
	Surface* screen;
	LevelMaps* levelMaps;
	AnimationState currentAnimationState = AnimationState::Down;
	AnimationState lastAnimationState = AnimationState::Down;
};
