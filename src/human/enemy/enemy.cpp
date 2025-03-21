﻿#include "precomp.h"
#include "enemy.h"

#include "src/audio/audioManager.h"
#include "src/audio/audioType.h"
#include "src/collider/aabb/boxAabb/boxAabb.h"
#include "src/collider/aabb/circleAabb/circleAabb.h"
#include "src/collider/boxCollider/boxCollider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/collider/sightCollider/sightCollider.h"
#include "src/human/player/player.h"
#include "src/managers/bullet/bulletManager.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/Tools/rng.h"
#include "src/tools/screenPrinter.h"

Enemy::Enemy(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager) : Human(pScreen, pLevelMaps, pSpriteStorage, pAudioManager)
{
	m_pSprite = new Sprite(*pSpriteStorage->GetSpriteData(SpriteType::Enemy)->sprite);
	m_pSprite->SetFrame(0);
	m_animationFrame = 0;

	m_pRng = new Rng();

	m_position = spawnPos;
	Enemy::SetSpeedToPatrolSpeed();

	m_pPlayer = pPlayer;
	m_pBulletManager = pBulletManager;

	m_movementDirection = spawnDir;
	m_movementDirectionAfterLookAround = spawnDir;
	m_movementDirectionBeforeLookAround = spawnDir;
	UpdateAnimationState();

	m_patrolCollider = new PointCollider(pScreen, pLevelMaps);

	m_pSightCollider = new SightCollider(pScreen, pLevelMaps, pPlayer);

	m_tileBoxCollider = new BoxCollider(pScreen, pLevelMaps, {30, 30});

	m_boxAabb = new BoxAabb(m_position, {static_cast<float>(m_pSprite->GetWidth()),static_cast<float>(m_pSprite->GetHeight())});

	m_broadPhaseCircleAabb = new CircleAabb(GetCenterPos(), BROAD_PHASE_CIRCLE_AABB_RADIUS);
}

Enemy::~Enemy()
{
	delete m_pRng;
	delete m_patrolCollider;
	delete m_pSightCollider;
	delete m_tileBoxCollider;
	delete m_boxAabb;
	delete m_broadPhaseCircleAabb;
}

void Enemy::Tick(float deltaTime)
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
			Shoot();
			UpdateTileBoxCollider();
			ChasePlayer(deltaTime);
			break;
		default:
			throw exception("Invalid enemy state");
	}

	UpdateAnimationState();
	Animate(deltaTime);
}

#ifdef _DEBUG
void Enemy::DrawColliders()
{
	if(m_state != EnemyState::Dead)
	{
		m_patrolCollider->Draw(2, 0x00ff00);

		m_pSightCollider->Draw(5, 0x35b0fc);

		m_tileBoxCollider->Draw(2, 0xff0000);

		if(m_debug_gotPunchedFrameCounter > 0)
		{
			m_boxAabb->Draw(m_pScreen, 0xffff00);
			m_debug_gotPunchedFrameCounter--;
		}
		else
		{
			m_boxAabb->Draw(m_pScreen);
		}

		m_broadPhaseCircleAabb->Draw(m_pScreen);
	}
	Debug_PrintValues();
}
#endif

#ifdef _DEBUG
void Enemy::Debug_PrintValues() const
{
	string stateString = {};
	switch(m_state)
	{
		case EnemyState::Patrol:
			stateString = "Patrol";
			break;
		case EnemyState::LookAround:
			stateString = "LookAround";
			break;
		case EnemyState::Alarm:
			stateString = "Alarm";
			break;
		case EnemyState::Dead:
			stateString = "Dead";
			break;
		case EnemyState::PunchShake:
			stateString = "PunchShake";
			break;
		case EnemyState::RedRelieve:
			stateString = "RedRelieve";
			break;
		case EnemyState::RedComeBack:
			stateString = "RedComeBack";
			break;
		case EnemyState::Hidden:
			stateString = "Hidden";
			break;
		default:
			throw exception("invalid state");
	}
	ScreenPrinter* screenPrinter = new ScreenPrinter();
	screenPrinter->Print(m_pScreen, "state:", stateString, m_position);
	screenPrinter->Print(m_pScreen, "hp:", m_hp, {m_position.x,m_position.y + 10});
	screenPrinter->Print(m_pScreen, "speed:", m_speed, {m_position.x,m_position.y + 20});
	delete screenPrinter;
}
#endif

float2 Enemy::GetCenterPos() const
{
	return
	{
		m_position.x + static_cast<float>(m_pSprite->GetWidth()) / 2.0f,
		m_position.y + static_cast<float>(m_pSprite->GetHeight()) / 2.0f
	};
}

void Enemy::UpdateBroadPhaseCircleAabb() const
{
	m_broadPhaseCircleAabb->UpdatePosition(GetCenterPos());
}


void Enemy::Draw() const
{
	if(m_state == EnemyState::Dead || m_state == EnemyState::Hidden)
	{
		return;
	}

	Human::Draw();
}

void Enemy::PlayerPunchReported()
{
	if(m_state == EnemyState::Dead)
	{
		return;
	}

	if(m_boxAabb->IsColliding(m_pPlayer->GetPunchBoxAabb()))
	{
#ifdef _DEBUG
		m_boxAabb->Draw(m_pScreen, 0xffff00);
		constexpr int debug_gotPunchedFrameCount = 10;
		m_debug_gotPunchedFrameCounter = debug_gotPunchedFrameCount;
#endif
		m_pAudioManager->Play(AudioType::PunchHit);
		m_hp--;
		if(m_hp <= 0)
		{
			SwitchState(EnemyState::Dead);
		}
		else
		{
			m_yBeforePunchShake = m_position.y;
			m_punchShakeShootStopRemaining = PUNCH_SHAKE_SHOOT_STOP_DURATION;
			m_enemyStateBeforePunchShake = m_state;
			SwitchState(EnemyState::PunchShake);
			m_isPunchShakePlaying = true;
		}
	}
}

void Enemy::OneEnemyAlarmedReport()
{
	SwitchState(EnemyState::Alarm);
}

void Enemy::UpdatePatrolCollider() const
{
	float2 center = GetCenterPos();
	float2 feet = center;
	feet.y += TILESET_TILEHEIGHT * 1.5f;

	float2 offset = {0, 0};
	switch(m_movementDirection)
	{
		case Direction::Up:
			offset.y = patrolColliderYOffset;
			break;
		case Direction::Down:
			offset.y = -patrolColliderYOffset;
			break;
		case Direction::Left:
			offset.x = patrolColliderXOffset;
			break;
		case Direction::Right:
			offset.x = -patrolColliderXOffset;
			break;
	}

	m_patrolCollider->UpdatePosition(feet + offset);
}

void Enemy::CheckSightCollider()
{
	if(m_pSightCollider->IsPlayerInSight())
	{
		SwitchState(EnemyState::Alarm);
	}
}

void Enemy::UpdateSightCollider() const
{
	m_pSightCollider->UpdatePosition(GetSightColliderPos(), m_movementDirection);
}

void Enemy::UpdateSightCollider(Direction direction) const
{
	m_pSightCollider->UpdatePosition(GetSightColliderPos(), direction);
}

void Enemy::CheckPatrolCollider()
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
		case TileType::ESD:
		case TileType::ESL:
		case TileType::ESR:
		case TileType::Door:
		case TileType::Hide:
		case TileType::Elevator:
			// do nothing
			break;
		case TileType::EPU:
			m_movementDirectionAfterLookAround = Direction::Up;
			break;
		case TileType::EPD:
			m_movementDirectionAfterLookAround = Direction::Down;
			break;
		case TileType::EPL:
			m_movementDirectionAfterLookAround = Direction::Left;
			break;
		case TileType::EPR:
			m_movementDirectionAfterLookAround = Direction::Right;
			break;
		default:
			throw exception("Invalid tile type");
	}

	if(m_movementDirectionAfterLookAround != m_movementDirection)
	{
		m_movementDirectionBeforeLookAround = m_movementDirection;
		SwitchState(EnemyState::LookAround);
	}
}

void Enemy::Lookaround(const float deltaTime)
{
	m_speed = 0.0f;

	if(m_lookAroundChecksDone >= TOTAL_DIRECTIONS)
	{
		m_lookAroundChecksDone = 0;
		SwitchState(EnemyState::Patrol);
		SetSpeedToPatrolSpeed();
		m_movementDirection = m_movementDirectionAfterLookAround;
		m_isOneStageOfLookOutPlaying = false;
		return;
	}

	if(m_isOneStageOfLookOutPlaying)
	{
		m_lookaroundTimer += deltaTime;
		if(m_lookaroundTimer > LOOKAROUND_TIME)
		{
			m_lookaroundTimer = 0.0f;
			m_isOneStageOfLookOutPlaying = false;
		}
	}
	else
	{
		int chance = m_pRng->BetweenInclusive(0, 100);
		if(chance > LOOKAROUND_CHANCE &&
		   static_cast<Direction>(m_lookAroundChecksDone) != m_movementDirectionBeforeLookAround &&
		   static_cast<Direction>(m_lookAroundChecksDone) != m_movementDirectionAfterLookAround)
		{
			m_movementDirection = static_cast<Direction>(m_lookAroundChecksDone);
			m_isOneStageOfLookOutPlaying = true;
		}
		else
		{
			m_isOneStageOfLookOutPlaying = false;
		}
		m_lookAroundChecksDone++;
	}
}

void Enemy::MoveInDirection(const float deltaTime)
{
	switch(m_movementDirection)
	{
		case Direction::Up:
			m_position.y -= m_speed * deltaTime;
			break;
		case Direction::Down:
			m_position.y += m_speed * deltaTime;
			break;
		case Direction::Left:
			m_position.x -= m_speed * deltaTime;
			break;
		case Direction::Right:
			m_position.x += m_speed * deltaTime;
			break;
	}
}


void Enemy::UpdateAnimationState()
{
	switch(m_movementDirection)
	{
		case Direction::Up:
			m_currentAnimationState = AnimationType::Up;
			break;
		case Direction::Down:
			m_currentAnimationState = AnimationType::Down;
			break;
		case Direction::Left:
			m_currentAnimationState = AnimationType::Left;
			break;
		case Direction::Right:
			m_currentAnimationState = AnimationType::Right;
			break;
	}
}

void Enemy::Animate(const float deltaTime)
{
	if(m_speed == 0.0f)
	{
		m_animationFrame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		m_pSprite->SetFrame(m_animationFrame);
		animationUpdateTimer = ANIMATION_UPDATE_TIME;
		return;
	}

	if(m_currentAnimationState != m_lastAnimationState)
	{
		m_animationFrame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		m_lastAnimationState = m_currentAnimationState;
		animationUpdateTimer = ANIMATION_UPDATE_TIME;
	}

	animationUpdateTimer += deltaTime;

	if(animationUpdateTimer > ANIMATION_UPDATE_TIME)
	{
		animationUpdateTimer = 0.0f;

		m_animationFrame++;
		if(m_animationFrame > animations[static_cast<int>(m_currentAnimationState)].endFrame)
		{
			m_animationFrame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		}

		m_pSprite->SetFrame(m_animationFrame);
	}
}

void Enemy::ChasePlayer(const float deltaTime)
{
	// should not move for a while after shooting
	if(m_shootStopRemaining > 0 || m_punchShakeShootStopRemaining > 0)
	{
		m_speed = 0.0f;
		return;
	}

	SetSpeedToChaseSpeed();

	// set positions to player and enemy's feet
	const float2 playerPos = m_pPlayer->GetFeetPos();
	const float2 pos = GetSightColliderPos();

	// calculate distance
	const float yDistance = abs(playerPos.y - pos.y);
	const float xDistance = abs(playerPos.x - pos.x);

	// stop (and shoot) if player is in sight
	if(m_pSightCollider->IsPlayerInSight())
	{
		m_speed = 0.0f;
		return;
	}

	m_chaseNoMovementCount++;

	// if hit a wall, change direction
	if(m_tileBoxCollider->IsSolid(m_movementDirection))
	{
		if(m_chaseNoMovementCount < 2)
		{
			switch(m_movementDirection)
			{
				case Direction::Up:
				case Direction::Down:
					m_movementDirection = playerPos.x >= pos.x ? Direction::Right : Direction::Left;
					break;
				case Direction::Left:
				case Direction::Right:
					m_movementDirection = playerPos.y >= pos.y ? Direction::Down : Direction::Up;
					break;
			}
		}
		else
		{
			// we count the times that the direction has changed but the enemy couldn't move.
			// if this number gets bigger than a certain number, it means that the enemy is stuck,
			// so we change to a new direction somewhat randomly.
			m_movementDirection = static_cast<Direction>((static_cast<int>(m_movementDirection) + m_pRng->BetweenInclusive(1, 2)) % TOTAL_DIRECTIONS);
		}

		return;
	}

	// if enemy is near the edge of the screen, change direction
	// moving enemy back a little is to prevent it from getting stuck
	int screenEdgeSize = TILESET_TILEWIDTH * 2;
	if(pos.x < screenEdgeSize)
	{
		m_movementDirection = playerPos.y >= pos.y ? Direction::Down : Direction::Up;
		m_position.x += 1;
		return;
	}
	if(pos.x > SCRWIDTH - screenEdgeSize)
	{
		m_movementDirection = playerPos.y >= pos.y ? Direction::Down : Direction::Up;
		m_position.x -= 1;
		return;
	}
	if(pos.y < screenEdgeSize)
	{
		m_movementDirection = playerPos.x >= pos.x ? Direction::Right : Direction::Left;
		m_position.y += 1;
		return;
	}
	if(pos.y > SCRHEIGHT - screenEdgeSize)
	{
		m_movementDirection = playerPos.x >= pos.x ? Direction::Right : Direction::Left;
		m_position.y -= 1;
		return;
	}

	// if player's x or y is close enough, and player is in sight in that direction, change direction
	if(xDistance < 1 && (m_movementDirection == Direction::Left || m_movementDirection == Direction::Right))
	{
		if(playerPos.y >= pos.y)
		{
			UpdateSightCollider(Direction::Down);
			if(m_pSightCollider->IsPlayerInSight())
			{
				m_movementDirection = Direction::Down;
				m_speed = 0.0f;
				return;
			}
		}
		else
		{
			UpdateSightCollider(Direction::Up);
			if(m_pSightCollider->IsPlayerInSight())
			{
				m_movementDirection = Direction::Up;
				m_speed = 0.0f;
				return;
			}
		}
	}
	else if(yDistance < 1 && (m_movementDirection == Direction::Up || m_movementDirection == Direction::Down))
	{
		if(playerPos.x >= pos.x)
		{
			UpdateSightCollider(Direction::Right);
			if(m_pSightCollider->IsPlayerInSight())
			{
				m_movementDirection = Direction::Right;
				m_speed = 0.0f;
				return;
			}
		}
		else
		{
			UpdateSightCollider(Direction::Left);
			if(m_pSightCollider->IsPlayerInSight())
			{
				m_movementDirection = Direction::Left;
				m_speed = 0.0f;
				return;
			}
		}
	}

	m_chaseNoMovementCount = 0;
	MoveInDirection(deltaTime);
}

void Enemy::Shoot()
{
	if(m_shootTimer <= 0 && m_punchShakeShootStopRemaining < 0)
	{
		m_shootTimer = SHOOT_TIME;
		m_shootStopRemaining = SHOOT_STOP_DURATION;
		float2 bulletDirection = m_pPlayer->GetCenterPos() - GetCenterPos();
		float2 bulletSpawnPos = GetCenterPos();
		m_pBulletManager->SpawnNewBullet(bulletSpawnPos, bulletDirection);
		m_pAudioManager->Play(AudioType::Shoot);
	}
}

int2 Enemy::GetSightColliderPos() const
{
	const int2 feet =
	{
		static_cast<int>(m_position.x) + m_pSprite->GetWidth() / 2,
		static_cast<int>(m_position.y + TILESET_TILEHEIGHT * 1.5f) + m_pSprite->GetHeight() / 2
	};
	return feet;
}

void Enemy::UpdateBoxAabb() const
{
	m_boxAabb->UpdatePosition(m_position);
}

void Enemy::UpdateTimers(const float deltaTime)
{
	m_shootTimer -= deltaTime;
	m_shootStopRemaining -= deltaTime;
	m_punchShakeShootStopRemaining -= deltaTime;
}

/* My original idea for making this animation was to use a timer-based logic,
 * where I moved the enemy up for some time, then move it back down for some time.
 * but it could become complex and very inaccurate. The idea (but no code) of doing it without a timer,
 * and using distances instead, came from my friend Hossein. Now this is a very solid and precise system.
 */
void Enemy::PunchShake(float deltaTime)
{
	if(m_isPunchShakeDirectionUp && m_yBeforePunchShake - m_position.y > PUNCH_SHAKE_MAX_DISTANCE)
	{
		m_isPunchShakeDirectionUp = false;
	}
	const float dir = m_isPunchShakeDirectionUp ? -1.0f : 1.0f;
	m_position.y += dir * PUNCH_SHAKE_SPEED * deltaTime;

	if(!m_isPunchShakeDirectionUp && m_position.y > m_yBeforePunchShake)
	{
		m_position.y = m_yBeforePunchShake;
		m_isPunchShakePlaying = false;
		m_isPunchShakeDirectionUp = true;

		/*
		 * if you want the enemies to not be alarmed after being punched (like the original game),
		 * uncomment the 1st line and comment the 2nd line below,
		 * otherwise, if you want the enemy to get alarmed and also alarm other enemies as soon as you punch them,
		 * comment the 1st line and uncomment the 2nd line below.
		 */
		//SwitchState(m_enemyStateBeforePunchShake); // reference game behavior
		SwitchState(EnemyState::Alarm);	 // what I believe makes more sense
	}
}

void Enemy::SwitchState(const EnemyState newState)
{
	/* if enemy is dead
	 * or the new state is what we already are in
	 * or new state is not dead, and punch shake animation is being played.
	 * this means that punch shake animation can not be interrupted with any state other than dead.
	 */
	if(m_state == EnemyState::Dead ||
	   m_state == newState ||
	   (m_isPunchShakePlaying && newState != EnemyState::Dead))
	{
		return;
	}

	m_state = newState;
}

void Enemy::SetSpeedToChaseSpeed()
{
	m_speed = SPEED_CHASE;
}

void Enemy::SetSpeedToPatrolSpeed()
{
	m_speed = SPEED_PATROL;
}
