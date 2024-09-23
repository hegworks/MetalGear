#include "precomp.h"
#include "spriteData.h"
#include "SpriteStorage.h"

SpriteStorage::SpriteStorage()
{
	playerData = new SpriteData{new Sprite(new Surface("assets/graphics/playerSheet.png"), 42) ,42};
	//enemyData = new SpriteData{new Sprite(new Surface("assets/graphics/enemy.png"), 1) ,1};
}

SpriteData* SpriteStorage::GetSpriteData(SpriteType spriteType)
{
	switch(spriteType)
	{
		case SpriteType::Player:
			return playerData;
		//case SpriteType::Enemy:
		//	return enemyData;
		default:
			throw exception("Invalid sprite type");
	}
}
