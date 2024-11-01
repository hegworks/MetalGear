﻿#include "precomp.h"
#include "winScreen.h"

WinScreen::WinScreen()
{
	m_sprite = new Sprite(new Surface("assets/graphics/winScreen.png"), 1);
}

WinScreen::~WinScreen()
{
	delete m_sprite;
}

void WinScreen::Draw(Surface* pScreen) const
{
	m_sprite->Draw(pScreen, 0, 0);
}
