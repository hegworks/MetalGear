﻿#include "precomp.h"
#include "loseScreen.h"

LoseScreen::LoseScreen()
{
	m_sprite = new Sprite(new Surface("assets/graphics/loseScreen.png"), 1);
}

LoseScreen::~LoseScreen()
{
	delete m_sprite;
}

void LoseScreen::Draw(Surface* pScreen) const
{
	m_sprite->Draw(pScreen, 0, 0);
}
