#pragma once

class PixelPerfectCollisionChecker;
class LevelMaps;
class SpriteStorage;
class BulletManager;
class Player;
class PointCollider;

class Bullet
{
public:
	Bullet(int id, float2 startPos, float2 direction, Surface* pScreen, Player* pPlayer, SpriteStorage* pSpriteStorage, LevelMaps* pLevelMaps, PixelPerfectCollisionChecker* pPixelPerfectCollisionChecker);
	void Tick(float deltaTime);
	void Activate(float2 startPos, float2 direction);
	void Deactivate();
	void Draw() const;

	int GetId() const { return m_id; }
	bool IsActive() const { return m_isActive; }

private:
	float2 m_pos{};
	float2 m_dir{};
	float m_speed = 0.6f;
	int m_id = -1;
	bool m_isActive = false;

	// fix spawn in a wall variables
	bool m_wasInWallWhenSpawned = false;
	int m_spawnedInWallTileRow = -1;
	bool m_wasOneTileLowerSolidWhenSpawned = false;
	bool m_hasPassedANonSolid = false;

	PointCollider* m_pPointCollider = nullptr;
	Player* m_pPlayer = nullptr;
	Surface* m_pScreen = nullptr;
	Sprite* m_pSprite = nullptr;
	PixelPerfectCollisionChecker* m_pPixelPerfectCollisionChecker = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;

	void UpdatePointCollider() const;
	void Move(float deltaTime);
	void CheckPointCollider();
	void CheckPlayerCollision();
	void CheckOutOfScreen();
};
