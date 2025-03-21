﻿#pragma once

class PixelPerfectCollisionChecker;
class SpriteStorage;
class Bullet;
class LevelMaps;
class Player;

constexpr int MAX_BULLETS = 20;

class BulletManager
{
public:
	BulletManager(Surface* pScreen, LevelMaps* pLevelMaps, Player* pPlayer, SpriteStorage* pSpriteStorage, PixelPerfectCollisionChecker* pPixelPerfectCollisionChecker);
	~BulletManager();
	void Tick(float deltaTime);
	void Draw() const;
	void SpawnNewBullet(float2 startPos, float2 direction) const;
	void RoomChanged() const;

private:
	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
	Player* m_pPlayer = nullptr;
	Bullet* m_pBullets[MAX_BULLETS] = {};

	Bullet* GetFirstInactiveBullet() const;
};
