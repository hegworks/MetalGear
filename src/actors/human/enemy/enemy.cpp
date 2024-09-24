#include "precomp.h"
#include "enemy.h"

Enemy::Enemy(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, float2 spawnPos, Direction spawnDir) : Human(screen, levelMaps, spriteStorage)
{
	sprite = spriteStorage->GetSpriteData(SpriteType::Enemy)->sprite;
	sprite->SetFrame(0);

	animationFrame = 0;
	position = spawnPos;
	speed = 0.25f;

	switch(spawnDir)
	{
		case Direction::Up:
			sprite->SetFrame(6);
			break;
		case Direction::Down:
			sprite->SetFrame(0);
			break;
		case Direction::Left:
			sprite->SetFrame(3);
			break;
		case Direction::Right:
			sprite->SetFrame(9);
			break;
	}
}