#include "precomp.h"
#include "human.h"

Human::Human()
{
}

Human::~Human()
{
}

void Human::Draw(Surface* screen)
{
	graphic->Draw(screen, position.x, position.y);
}

void Human::Move(int2 direction)
{
}

void Human::Tick(float deltaTime)
{
}
