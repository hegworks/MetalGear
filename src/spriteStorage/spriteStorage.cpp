#include "precomp.h"
#include "spriteData.h"
#include "SpriteStorage.h"

SpriteStorage::SpriteStorage()
{
	m_playerData = new SpriteData{new Sprite(new Surface("assets/graphics/playerSheet.png"), 42) ,42};
	m_playerHurtData = new SpriteData{new Sprite(new Surface("assets/graphics/playerHurtSheet.png"), 42) ,42};
	m_enemyData = new SpriteData{new Sprite(new Surface("assets/graphics/enemySheet.png"), 12) ,12};
	m_bulletData = new SpriteData{new Sprite(new Surface("assets/graphics/bullet.png"), 1) ,1};
	m_enemyRedData = new SpriteData{new Sprite(new Surface("assets/graphics/enemyRedSheet.png"), 12) ,12};
}

SpriteStorage::~SpriteStorage()
{
	delete m_playerData->sprite;
	delete m_playerData;
	delete m_playerHurtData->sprite;
	delete m_playerHurtData;
	delete m_enemyData->sprite;
	delete m_enemyData;
	delete m_bulletData->sprite;
	delete m_bulletData;
	delete m_enemyRedData->sprite;
	delete m_enemyRedData;
}

SpriteData* SpriteStorage::GetSpriteData(SpriteType spriteType) const
{
	switch(spriteType)
	{
		case SpriteType::Player:
			return m_playerData;
		case SpriteType::PlayerHurt:
			return m_playerHurtData;
		case SpriteType::Enemy:
			return m_enemyData;
		case SpriteType::Bullet:
			return m_bulletData;
		case SpriteType::EnemyRed:
			return m_enemyRedData;
		default:
			throw exception("Invalid sprite type");
	}
}
