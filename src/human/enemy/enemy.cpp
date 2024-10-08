#include "precomp.h"
#include "enemy.h"

#include "src/collider/aabb/boxAabb.h"
#include "src/collider/boxCollider/boxCollider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/collider/sightCollider/sightCollider.h"
#include "src/human/player/player.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/Tools/rng.h"
#include "src/tools/screenPrinter.h"

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

	tileBoxCollider = new BoxCollider(pScreen, pLevelMaps, {30, 30});

	m_boxAabb = new BoxAabb(m_position, {static_cast<float>(m_pSprite->GetWidth()),static_cast<float>(m_pSprite->GetHeight())});
}

void Enemy::Tick(float deltaTime)
{
	if(state == EnemyState::Dead)
	{
		return;
	}

	UpdateSightCollider();
	CheckSightCollider();
	UpdateBoxAabb();

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
			UpdateTileBoxCollider();
			ChasePlayer(deltaTime);
			break;
		case EnemyState::Dead:
			return;
		default:
			throw exception("Invalid enemy state");
	}

	UpdateAnimationState();
	Animate(deltaTime);
}

void Enemy::DrawColliders()
{
	if(state != EnemyState::Dead)
	{
		patrolCollider->Draw(2, 0x00ff00);

		m_pSightCollider->Draw(5, 0x35b0fc);

		tileBoxCollider->Draw(2, 0xff0000);

		if(m_debug_gotPunchedFrameCounter > 0)
		{
			m_boxAabb->Draw(m_pScreen, 0xffff00);
			m_debug_gotPunchedFrameCounter--;
		}
		else
		{
			m_boxAabb->Draw(m_pScreen);
		}
	}
	Debug_PrintValues();
}

void Enemy::Debug_PrintValues() const
{
	ScreenPrinter* screenPrinter = new ScreenPrinter();
	string stateString = {};
	switch(state)
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
		default:
			throw new exception("invalid state");
	}
	screenPrinter->Print(m_pScreen, "state:", stateString, m_position);
	screenPrinter->Print(m_pScreen, "hp:", m_hp, {m_position.x,m_position.y + 10});
	screenPrinter->Print(m_pScreen, "speed:", m_speed, {m_position.x,m_position.y + 20});

}


void Enemy::Draw() const
{
	if(state == EnemyState::Dead)
	{
		return;
	}

	Human::Draw();
}

void Enemy::PlayerPunchReported()
{
	if(state == EnemyState::Dead)
	{
		return;
	}

	if(m_boxAabb->IsColliding(m_pPlayer->GetPunchBoxAabb()))
	{
		printf("PLAYER PUNCHED ENEMY!\n");
		m_boxAabb->Draw(m_pScreen, 0xffff00);
		m_hp--;
		int debug_gotPunchedFrameCount = 10;
		m_debug_gotPunchedFrameCounter = debug_gotPunchedFrameCount;
		if(m_hp <= 0)
		{
			state = EnemyState::Dead;
		}
	}
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
	}
}

void Enemy::UpdateSightCollider() const
{
	m_pSightCollider->UpdatePosition(GetSightColliderPos(), movementDirection);
}

void Enemy::UpdateSightCollider(Direction direction) const
{
	m_pSightCollider->UpdatePosition(GetSightColliderPos(), direction);
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
	if(m_speed == 0.0f)
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
	m_speed = SPEED_CHASE;

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

	chaseNoMovementCount++;

	// if hit a wall, change direction
	if(tileBoxCollider->IsSolid(movementDirection))
	{
		if(chaseNoMovementCount < 2)
		{
			switch(movementDirection)
			{
				case Direction::Up:
				case Direction::Down:
					movementDirection = playerPos.x >= pos.x ? Direction::Right : Direction::Left;
					break;
				case Direction::Left:
				case Direction::Right:
					movementDirection = playerPos.y >= pos.y ? Direction::Down : Direction::Up;
					break;
			}
		}
		else
		{
			// we count the times that the direction has changed but the enemy couldn't move.
			// if this number gets bigger than a certain number, it means that the enemy is stuck,
			// so we change to a new direction somewhat randomly.
			movementDirection = static_cast<Direction>((static_cast<int>(movementDirection) + rng->BetweenInclusive(1, 2)) % TOTAL_DIRECTIONS);
		}

		return;
	}

	// if enemy is near the edge of the screen, change direction
	// moving enemy back a little is to prevent it from getting stuck
	int screenEdgeSize = TILESET_TILEWIDTH * 2;
	if(pos.x < screenEdgeSize)
	{
		movementDirection = playerPos.y >= pos.y ? Direction::Down : Direction::Up;
		m_position.x += 1;
		return;
	}
	if(pos.x > SCRWIDTH - screenEdgeSize)
	{
		movementDirection = playerPos.y >= pos.y ? Direction::Down : Direction::Up;
		m_position.x -= 1;
		return;
	}
	if(pos.y < screenEdgeSize)
	{
		movementDirection = playerPos.x >= pos.x ? Direction::Right : Direction::Left;
		m_position.y += 1;
		return;
	}
	if(pos.y > SCRHEIGHT - screenEdgeSize)
	{
		movementDirection = playerPos.x >= pos.x ? Direction::Right : Direction::Left;
		m_position.y -= 1;
		return;
	}

	// if player's x or y is close enough, and player is in sight in that direction, change direction
	if(xDistance < 1 && (movementDirection == Direction::Left || movementDirection == Direction::Right))
	{
		if(playerPos.y >= pos.y)
		{
			UpdateSightCollider(Direction::Down);
			if(m_pSightCollider->IsPlayerInSight())
			{
				movementDirection = Direction::Down;
				m_speed = 0.0f;
				return;
			}
		}
		else
		{
			UpdateSightCollider(Direction::Up);
			if(m_pSightCollider->IsPlayerInSight())
			{
				movementDirection = Direction::Up;
				m_speed = 0.0f;
				return;
			}
		}
	}
	else if(yDistance < 1 && (movementDirection == Direction::Up || movementDirection == Direction::Down))
	{
		if(playerPos.x >= pos.x)
		{
			UpdateSightCollider(Direction::Right);
			if(m_pSightCollider->IsPlayerInSight())
			{
				movementDirection = Direction::Right;
				m_speed = 0.0f;
				return;
			}
		}
		else
		{
			UpdateSightCollider(Direction::Left);
			if(m_pSightCollider->IsPlayerInSight())
			{
				movementDirection = Direction::Left;
				m_speed = 0.0f;
				return;
			}
		}
	}

	chaseNoMovementCount = 0;
	MoveInDirection(deltaTime);
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
