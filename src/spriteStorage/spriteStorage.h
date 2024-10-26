#pragma once
#include "spriteData.h"
#include "spriteType.h"

class SpriteStorage
{
public:
	SpriteStorage();
	SpriteData* GetSpriteData(SpriteType spriteType) const;

private:
	SpriteData* m_playerData = nullptr;
	SpriteData* m_playerHurtData = nullptr;
	SpriteData* m_enemyData = nullptr;
	SpriteData* m_bulletData = nullptr;
	SpriteData* m_enemyRedData = nullptr;
};
