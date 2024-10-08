#include "precomp.h"
#include "direction.h"
#include "human.h"
#include "src/collider/boxCollider/boxCollider.h"

Human::Human(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage)
{
	m_pScreen = pScreen;
	m_pLevelMaps = pLevelMaps;
	m_pSpriteStorage = pSpriteStorage;
}

void Human::Draw() const
{
	if(!m_pSprite)
		throw exception("sprite doesn't exist");

	m_pSprite->Draw(m_pScreen, static_cast<int>(m_position.x), static_cast<int>(m_position.y));
}

void Human::UpdateTileBoxCollider() const
{
	int2 feet =
	{
		static_cast<int>(m_position.x) + tileBoxColliderXOffset,
		static_cast<int>(m_position.y) + tileBoxColliderYOffset
	};
	switch(m_movementDirection)
	{
		case Direction::Up:
			feet.y -= tileCollisionPreventPixels;
			break;
		case Direction::Down:
			feet.y += tileCollisionPreventPixels;
			break;
		case Direction::Left:
			feet.x -= tileCollisionPreventPixels;
			break;
		case Direction::Right:
			feet.x += tileCollisionPreventPixels;
			break;
	}

	m_tileBoxCollider->UpdatePosition(feet);
}
