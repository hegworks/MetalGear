#pragma once
#include "src/actors/direction.h"
#include "src/actors/human/human.h"

class Enemy : public Human
{
public:
	Enemy(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, float2 spawnPos, Direction spawnDir);
};
