#include "precomp.h"
#include "human.h"

Human::Human(Surface* screen, LevelMaps* levelMaps)
{
	this->screen = screen;
	this->levelMaps = levelMaps;
}

Human::~Human() = default;

void Human::Draw() const
{
	graphic->Draw(screen, position.x, position.y);
}

void Human::Move(int2 direction)
{
}

void Human::Tick(float deltaTime)
{
}
