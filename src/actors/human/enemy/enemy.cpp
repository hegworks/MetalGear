#include "precomp.h"
#include "enemy.h"

Enemy::Enemy(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage) : Human(screen, levelMaps, spriteStorage)
{
	sprite = spriteStorage->GetSpriteData(SpriteType::Enemy)->sprite;
	sprite->SetFrame(0);

	animationFrame = 0;
	position = float2(512, 256);
	speed = 0.25f;
}