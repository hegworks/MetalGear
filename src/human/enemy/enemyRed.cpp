#include "precomp.h"
#include "enemyRed.h"

#include "src/collider/pointCollider/pointCollider.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/tile/tileType.h"
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

	if(m_isOrder1WaitingToSpawn)
	{
		CheckComeBackOrder1Spawn(deltaTime);
	}

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
			m_speed = SPEED;
			CheckSightCollider();
			MoveInDirection(deltaTime);
			break;
		case EnemyState::RedComeBack:
			CheckSightCollider();
			UpdatePatrolCollider();
			CheckLookAroundCollider();
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

void EnemyRed::ComeBack(int comebackOrder)
{
	m_comeBackOrder = comebackOrder;
	if(comebackOrder == 0)
	{
		m_position.x = SCRWIDTH;
		m_speed = SPEED;
		m_movementDirection = Direction::Left;
		SwitchState(EnemyState::RedComeBack);
	}
	else
	{
		m_isOrder1WaitingToSpawn = true;
	}
}

void EnemyRed::CheckLookAroundCollider()
{
	switch(m_patrolCollider->GetTileType())
	{
		case TileType::Empty:
		case TileType::Solid:
		case TileType::RC0:
		case TileType::RC1:
		case TileType::RC2:
		case TileType::RC3:
		case TileType::RC4:
		case TileType::ESU:
		case TileType::ESL:
		case TileType::ESR:
		case TileType::Door:
		case TileType::EPU:
		case TileType::EPD:
		case TileType::EPL:
		case TileType::EPR:
		case TileType::Elevator:
			// do nothing
			break;
		case TileType::ESD:
			if(m_comeBackOrder == 0 && m_position.x > ORDER_0_ESD_X)
			{
				// do nothing
			}
			else
			{
				m_state = EnemyState::LookAround;
			}
			break;
		default:
			throw exception("Invalid tile type");
	}
}

void EnemyRed::CheckComeBackOrder1Spawn(float deltaTime)
{
	if(m_comeBackOrder1SpawnTimer < COMEBACK_ORDER_1_SPAWN_TIME)
	{
		m_comeBackOrder1SpawnTimer += deltaTime;
		return;
	}
	m_comeBackOrder1SpawnTimer = 0;

	m_position.x = SCRWIDTH;
	m_movementDirection = Direction::Left;
	SwitchState(EnemyState::RedComeBack);
	m_isOrder1WaitingToSpawn = false;
}

void EnemyRed::Relieve()
{
	if(m_state == EnemyState::Alarm || m_state == EnemyState::RedRelieve)
	{
		return;
	}

	m_movementDirection = Direction::Right;
	SwitchState(EnemyState::RedRelieve);
}
