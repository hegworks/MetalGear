#include "precomp.h"
#include "spriteData.h"
#include "SpriteStorage.h"

SpriteStorage::SpriteStorage()
{
	m_playerData = new SpriteData{new Sprite(new Surface("assets/graphics/playerSheet.png"), 42) ,42};
	m_enemyData = new SpriteData{new Sprite(new Surface("assets/graphics/enemySheet.png"), 12) ,12};
	m_bulletData = new SpriteData{new Sprite(new Surface("assets/graphics/bullet.png"), 1) ,1};
}

SpriteData* SpriteStorage::GetSpriteData(SpriteType spriteType) const
{
	switch(spriteType)
	{
		case SpriteType::Player:
			return m_playerData;
		case SpriteType::Enemy:
			return m_enemyData;
		case SpriteType::Bullet:
			return m_bulletData;
		default:
			throw exception("Invalid sprite type");
	}
}
