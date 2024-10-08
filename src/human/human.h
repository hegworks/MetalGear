#pragma once
#include "direction.h"
#include "src/animation/animationState.h"
#include "src/tile/tileSet.h"

class BoxCollider;
class SpriteStorage;
class LevelMaps;

class Human
{
public:
	Human(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage);

	virtual void Draw() const;
	virtual void DrawColliders() {}
	virtual void Tick(float /* deltatime */) {}

protected:
	float2 m_position;

	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
	SpriteStorage* m_pSpriteStorage = nullptr;

	AnimationState m_currentAnimationState = AnimationState::Down;
	AnimationState m_lastAnimationState = AnimationState::Down;

	Sprite* m_pSprite = nullptr;

	Direction movementDirection = Direction::Down;

	float m_speed;
	int m_animationFrame;

	BoxCollider* tileBoxCollider = nullptr;
	const int tileBoxColliderXOffset = TILESET_TILEWIDTH - 8;
	const int tileBoxColliderYOffset = TILESET_TILEHEIGHT * 3 - 8;
	const int tileCollisionPreventPixels = 1;

	virtual void UpdateTileBoxCollider() const;
};
