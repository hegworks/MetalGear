#pragma once
#include "sprite.h"

class LoseScreen
{
public:
	LoseScreen();
	~LoseScreen();
	void Draw(Surface* pScreen) const;

private:
	Sprite* m_sprite;
};
