#pragma once

class HudManager
{
public:
	HudManager(Surface* pScreen);
	~HudManager();
	void Draw() const;
	void PlayerHpChanged(int hp);

private:
	Surface* m_pScreen = nullptr;
	Sprite* m_pBgSprite = nullptr; // background sprite

	const int2 BG_POS = {0,768};

	// hp
	Sprite* m_pHpFillSprite = nullptr; // background sprite
	const int2 HP_FILL_POS = {202,789};
	float m_hpFillScale = 1;
	const int HP_MAX = 10;
	int m_hp = HP_MAX;

	void UpdateHpFill();
};
