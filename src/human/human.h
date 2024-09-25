#pragma once
#include "src/animation/animationState.h"

class SpriteStorage;
class LevelMaps;

class Human
{
public:
	Human(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage);
	~Human();

	void Draw() const;
	virtual void DrawColliders() const {}
	virtual void Move(int2 direction) {}
	virtual void Tick(float deltaTime) {}

protected:
	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
	SpriteStorage* m_pSpriteStorage = nullptr;

	AnimationState m_currentAnimationState = AnimationState::Down;
	AnimationState m_lastAnimationState = AnimationState::Down;

	Sprite* m_pSprite = nullptr;

	float2 m_position;
	float m_speed;
	int m_animationFrame;
};
