#include "precomp.h"
#include "human.h"

Human::Human(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage)
{
	this->screen = screen;
	this->levelMaps = levelMaps;
	this->spriteStorage = spriteStorage;
}

Human::~Human() = default;

void Human::Draw() const
{
	if(!sprite)
		throw exception("sprite doesn't exist");

	sprite->Draw(screen, position.x, position.y);
}
