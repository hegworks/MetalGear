#include "precomp.h"
#include "enemyRed.h"

#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/Tools/rng.h"

EnemyRed::EnemyRed(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager) : Enemy(pScreen, pLevelMaps, pSpriteStorage, spawnPos, spawnDir, pPlayer, pBulletManager, pAudioManager)
{
	m_pSprite = new Sprite(*pSpriteStorage->GetSpriteData(SpriteType::EnemyRed)->sprite);
	SwitchState(EnemyState::LookAround);
}

void EnemyRed::Tick(float deltaTime)
{
	if(m_state == EnemyState::Dead)
	{
		return;
	}

	UpdateTimers(deltaTime);

	if(m_state == EnemyState::PunchShake)
	{
		PunchShake(deltaTime);
		return;
	}

	UpdateSightCollider();
	UpdateBoxAabb();
	UpdateBroadPhaseCircleAabb();

	switch(m_state)
	{
		case EnemyState::Patrol:
			// enemyRed doesn't have normal patrol state
			break;
		case EnemyState::LookAround:
			CheckSightCollider();
			Lookaround(deltaTime);
			break;
		case EnemyState::Alarm:
			Shoot(deltaTime);
			UpdateTileBoxCollider();
			ChasePlayer(deltaTime);
			break;
		case EnemyState::Dead:
		case EnemyState::PunchShake:
			// handled as early return on top of the function
			break;
		case EnemyState::RedRelieve:
		case EnemyState::RedComeBack:
			MoveInDirection(deltaTime);
			break;
		case EnemyState::Hidden:
			break;
		default:
			throw exception("Invalid enemy state");
	}

	UpdateAnimationState();
	Animate(deltaTime);
}

void EnemyRed::Lookaround(float deltaTime)
{
	m_speed = 0.0f;

	if(m_lookaroundTimer < LOOKAROUND_TIME)
	{
		m_lookaroundTimer += deltaTime;
		return;
	}
	m_lookaroundTimer = 0.0f;

	// increase current direction between 1 & 2. skip the up direction because up of red enemies is just wall.
	constexpr int minDir = static_cast<int>(Direction::Down);
	const int dirIncrease = m_pRng->BetweenInclusive(1, 2);
	int newDir = (static_cast<int>(m_movementDirection) + dirIncrease) % TOTAL_DIRECTIONS;
	if(newDir < minDir) newDir = minDir;
	m_movementDirection = static_cast<Direction>(newDir);
}
