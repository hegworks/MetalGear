#pragma once
#include "spriteData.h"
#include "spriteType.h"

class SpriteStorage
{
public:
	SpriteData* GetSpriteData(SpriteType spriteType) const;

	SpriteStorage();

private:
	SpriteData* m_playerData;
	SpriteData* m_enemyData;
	SpriteData* m_bulletData;
};
