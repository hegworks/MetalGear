#pragma once
#include "src/actors/human/human.h"

class Enemy : public Human
{
public:
	Enemy(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage);
};
