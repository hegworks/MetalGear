#pragma once
#include "direction.h"
#include "src/animation/animationState.h"
#include "src/tile/tileSet.h"

class CircleAabb;
class BoxCollider;
class SpriteStorage;
class LevelMaps;

class Human
{
public:
	Human(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage);

	virtual void Draw() const;
#ifdef _PHYSICS_DEBUG
	virtual void DrawColliders() {}
#endif
	virtual void Tick(float /* deltatime */) {}
	CircleAabb* GetBroadPhaseCircleAabb() const { return m_broadPhaseCircleAabb; }

protected:
	float2 m_position;

	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
	SpriteStorage* m_pSpriteStorage = nullptr;

	AnimationState m_currentAnimationState = AnimationState::Down;
	AnimationState m_lastAnimationState = AnimationState::Down;

	Sprite* m_pSprite = nullptr;

	Direction m_movementDirection = Direction::Down;

	float m_speed;
	int m_animationFrame;

	BoxCollider* m_tileBoxCollider = nullptr;
	const int tileBoxColliderXOffset = TILESET_TILEWIDTH - 8;
	const int tileBoxColliderYOffset = TILESET_TILEHEIGHT * 3 - 8;
	const int tileCollisionPreventPixels = 1;

	// broad-phase
	CircleAabb* m_broadPhaseCircleAabb = nullptr;
	const float BROAD_PHASE_CIRCLE_AABB_RADIUS = 96;
	virtual void UpdateBroadPhaseCircleAabb() const = 0;

	virtual void UpdateTileBoxCollider() const;
};
