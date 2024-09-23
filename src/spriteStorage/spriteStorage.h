#pragma once
#include "spriteData.h"
#include "spriteType.h"

class SpriteStorage
{
public:
	SpriteData* GetSpriteData(SpriteType spriteType);

	SpriteStorage();

private:
	SpriteData* playerData;
	SpriteData* enemyData;
};
