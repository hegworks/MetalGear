#include "precomp.h"
#include "enemy.h"

#include "src/collider/pointCollider/pointCollider.h"
#include "src/collider/sightCollider/sightCollider.h"
#include "src/human/player/player.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/Tools/rng.h"

Enemy::Enemy(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer) : Human(pScreen, pLevelMaps, pSpriteStorage)
{
	m_pSprite = new Sprite(*pSpriteStorage->GetSpriteData(SpriteType::Enemy)->sprite);
	m_pSprite->SetFrame(0);

	rng = new Rng();

	m_animationFrame = 0;
	m_position = spawnPos;
	m_speed = SPEED;

	m_pPlayer = pPlayer;

	movementDirection = spawnDir;
	movementDirectionAfterLookAround = spawnDir;
	movementDirectionBeforeLookAround = spawnDir;
	UpdateAnimationState();

	patrolCollider = new PointCollider(pScreen, pLevelMaps);

	m_pSightCollider = new SightCollider(pScreen, pLevelMaps, pPlayer);
}

void Enemy::Tick(float deltaTime)
{
	UpdateSightCollider();
	CheckSightCollider();

	switch(state)
	{
		case EnemyState::Patrol:
			UpdatePatrolCollider();
			CheckPatrolCollider();
			MoveInDirection(deltaTime);
			break;
		case EnemyState::LookAround:
			Lookaround(deltaTime);
			break;
		case EnemyState::Alarm:
			ChasePlayer(deltaTime);
			break;
		default:
			throw exception("Invalid enemy state");
	}

	UpdateAnimationState();
	Animate(deltaTime);
}

void Enemy::DrawColliders() const
{
	m_pScreen->Box(m_position.x, m_position.y, m_position.x + m_pSprite->GetWidth(), m_position.y + m_pSprite->GetHeight(), 0xff0000);

	patrolCollider->Draw(2, 0x00ff00);

	m_pSightCollider->Draw(5, 0x35b0fc);
}

void Enemy::UpdatePatrolCollider() const
{
	int2 center =
	{
		static_cast<int>(m_position.x) + m_pSprite->GetWidth() / 2,
		static_cast<int>(m_position.y) + m_pSprite->GetHeight() / 2
	};

	int2 feet = center;
	feet.y += TILESET_TILEHEIGHT * 1.5f;

	int2 offset = {0, 0};
	switch(movementDirection)
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

	patrolCollider->UpdatePosition(feet + offset);
}

void Enemy::CheckSightCollider()
{
	if(m_pSightCollider->IsPlayerInSight())
	{
		state = EnemyState::Alarm;
		m_pScreen->Bar(50, 50, 150, 150, 0xeb8e0c);
	}
}

void Enemy::UpdateSightCollider() const
{
	int2 feet =
	{
		static_cast<int>(m_position.x) + m_pSprite->GetWidth() / 2,
		static_cast<int>(m_position.y + TILESET_TILEHEIGHT * 1.5f) + m_pSprite->GetHeight() / 2
	};
	m_pSightCollider->UpdatePosition(feet, movementDirection);
}

void Enemy::CheckPatrolCollider()
{
	switch(patrolCollider->GetTileType())
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
			// do nothing
			break;
		case TileType::EPU:
			movementDirectionAfterLookAround = Direction::Up;
			break;
		case TileType::EPD:
			movementDirectionAfterLookAround = Direction::Down;
			break;
		case TileType::EPL:
			movementDirectionAfterLookAround = Direction::Left;
			break;
		case TileType::EPR:
			movementDirectionAfterLookAround = Direction::Right;
			break;
		default:
			throw exception("Invalid tile type");
	}

	if(movementDirectionAfterLookAround != movementDirection)
	{
		movementDirectionBeforeLookAround = movementDirection;
		state = EnemyState::LookAround;
	}
}

void Enemy::Lookaround(float deltaTime)
{
	m_speed = 0.0f;

	if(lookAroundChecksDone >= TOTAL_DIRECTIONS)
	{
		lookAroundChecksDone = 0;
		state = EnemyState::Patrol;
		m_speed = SPEED;
		movementDirection = movementDirectionAfterLookAround;
		isOneStageOfLookOutPlaying = false;
		return;
	}

	if(isOneStageOfLookOutPlaying)
	{
		lookaroundTimer += deltaTime;
		if(lookaroundTimer > LOOKAROUND_TIME)
		{
			lookaroundTimer = 0.0f;
			isOneStageOfLookOutPlaying = false;
		}
	}
	else
	{
		int chance = rng->BetweenInclusive(0, 100);
		if(chance > LOOKAROUND_CHANCE &&
		   static_cast<Direction>(lookAroundChecksDone) != movementDirectionBeforeLookAround &&
		   static_cast<Direction>(lookAroundChecksDone) != movementDirectionAfterLookAround)
		{
			movementDirection = static_cast<Direction>(lookAroundChecksDone);
			isOneStageOfLookOutPlaying = true;
		}
		else
		{
			isOneStageOfLookOutPlaying = false;
		}
		lookAroundChecksDone++;
	}
}

void Enemy::MoveInDirection(float deltaTime)
{
	switch(movementDirection)
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
	switch(movementDirection)
	{
		case Direction::Up:
			m_currentAnimationState = AnimationState::Up;
			break;
		case Direction::Down:
			m_currentAnimationState = AnimationState::Down;
			break;
		case Direction::Left:
			m_currentAnimationState = AnimationState::Left;
			break;
		case Direction::Right:
			m_currentAnimationState = AnimationState::Right;
			break;
	}
}

void Enemy::Animate(float deltaTime)
{
	if(state == EnemyState::LookAround)
	{
		m_pSprite->SetFrame(animations[static_cast<int>(m_currentAnimationState)].startFrame);
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

void Enemy::ChasePlayer(float deltaTime)
{
	m_speed = SPEED * 2.0f;

	float2 playerPos = m_pPlayer->GetPosition();

	if(playerPos.y >= m_position.y + 20)
	{
		movementDirection = Direction::Down;
	}
	else if(playerPos.y < m_position.y)
	{
		movementDirection = Direction::Up;
	}
	else if(playerPos.x >= m_position.x + 20)
	{
		movementDirection = Direction::Right;
	}
	else if(playerPos.x < m_position.x)
	{
		movementDirection = Direction::Left;
	}

	MoveInDirection(deltaTime);
}
