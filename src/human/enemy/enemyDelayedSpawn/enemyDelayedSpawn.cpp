#include "precomp.h"
#include "enemyDelayedSpawn.h"

#include "src/collider/pointCollider/pointCollider.h"
#include "src/tile/tileType.h"
#include "src/tools/screenPrinter.h"

EnemyDelayedSpawn::EnemyDelayedSpawn(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager) :
	Enemy(pScreen, pLevelMaps, pSpriteStorage, spawnPos, spawnDir, pPlayer, pBulletManager, pAudioManager)
{
	SwitchState(EnemyState::Hidden);
}

void EnemyDelayedSpawn::Tick(float deltaTime)
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
			CheckSightCollider();
			UpdatePatrolCollider();
			CheckPatrolCollider();
			MoveInDirection(deltaTime);
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
		case EnemyState::Hidden:
			m_speed = 0;
			CheckHiddenTimer(deltaTime);
			break;
		default:
			throw exception("Invalid enemy state");
	}

	UpdateAnimationState();
	Animate(deltaTime);
}

void EnemyDelayedSpawn::CheckPatrolCollider()
{
	if(m_patrolCollider->GetTileType() == TileType::Hide)
	{
		SwitchState(EnemyState::Hidden);
	}
	else
	{
		Enemy::CheckPatrolCollider();
	}
}

#ifdef _DEBUG
void EnemyDelayedSpawn::DrawColliders()
{
	Enemy::DrawColliders();
	ScreenPrinter* screenPrinter = new ScreenPrinter();
	screenPrinter->Print(m_pScreen, "m_hiddenTimer: ", m_hiddenTimer, {m_position.x,m_position.y + 30});
	delete screenPrinter;
}
#endif

void EnemyDelayedSpawn::CheckHiddenTimer(float deltaTime)
{
	if(m_hiddenTimer < HIDDEN_TIME)
	{
		m_hiddenTimer += deltaTime;
		return;
	}
	m_hiddenTimer = 0;

	m_movementDirection = Direction::Down;
	m_movementDirectionAfterLookAround = Direction::Down;
	m_movementDirectionBeforeLookAround = Direction::Down;
	m_position.y += TILESET_TILEWIDTH * 2;
	SetSpeedToPatrolSpeed();
	m_state = EnemyState::Patrol;
}
