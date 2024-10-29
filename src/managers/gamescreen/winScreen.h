#pragma once

class WinScreen
{
public:
	WinScreen();
	~WinScreen();
	void Draw(Surface* pScreen) const;

private:
	Sprite* m_sprite;
};
