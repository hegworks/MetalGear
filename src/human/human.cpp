#include "precomp.h"
#include "human.h"

Human::Human(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage)
{
	m_pScreen = pScreen;
	m_pLevelMaps = pLevelMaps;
	m_pSpriteStorage = pSpriteStorage;
}

Human::~Human() = default;

void Human::Draw() const
{
	if(!m_pSprite)
		throw exception("sprite doesn't exist");

	m_pSprite->Draw(m_pScreen, m_position.x, m_position.y);
}
