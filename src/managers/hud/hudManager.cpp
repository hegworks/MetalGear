#include "precomp.h"
#include "hudManager.h"

#include "src/tools/mathExtra.h"

HudManager::HudManager(Surface* pScreen)
{
	m_pScreen = pScreen;
	m_pBgSprite = new Sprite(new Surface("assets/graphics/hud/background.png"), 1);
	m_pHpFillSprite = new Sprite(new Surface("assets/graphics/hud/hpFill.png"), 1);
}

HudManager::~HudManager()
{
	delete m_pBgSprite;
	delete m_pHpFillSprite;
}

void HudManager::Draw() const
{
	m_pBgSprite->Draw(m_pScreen, BG_POS.x, BG_POS.y);

	m_pHpFillSprite->DrawScaled(HP_FILL_POS.x, HP_FILL_POS.y, static_cast<int>(static_cast<float>(m_pHpFillSprite->GetWidth()) * m_hpFillScale), m_pHpFillSprite->GetHeight(), m_pScreen);
}

void HudManager::PlayerHpChanged(int hp)
{
	m_hp = hp;
	UpdateHpFill();
}

void HudManager::UpdateHpFill()
{
	m_hpFillScale = static_cast<float>(map_numbers(0, HP_MAX, 0, 1, m_hp));
}
