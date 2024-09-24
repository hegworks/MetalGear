#include "precomp.h"
#include "enemy.h"

#include "src/tile/tileSet.h"

Enemy::Enemy(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, float2 spawnPos, Direction spawnDir) : Human(screen, levelMaps, spriteStorage)
{
	sprite = new Sprite(*spriteStorage->GetSpriteData(SpriteType::Enemy)->sprite);
	sprite->SetFrame(0);

	animationFrame = 0;
	position = spawnPos;
	speed = 0.2f;

	movementDirection = spawnDir;
	UpdateAnimationState();

	patrolCollider = new PointCollider(screen, levelMaps);
}

void Enemy::Tick(float deltaTime)
{
	UpdateColliders();
	CheckPatrolCollider();
	UpdatePosition(deltaTime);
	UpdateAnimationState();
	Animate(deltaTime);
}

void Enemy::DrawColliders() const
{
	screen->Box(position.x, position.y, position.x + sprite->GetWidth(), position.y + sprite->GetHeight(), 0xff0000);

	patrolCollider->Draw(2, 0x00ff00);
}

void Enemy::UpdateColliders()
{
	UpdatePatrolCollider();
}

void Enemy::UpdatePatrolCollider() const
{
	int2 center =
	{
		static_cast<int>(position.x) + sprite->GetWidth() / 2,
		static_cast<int>(position.y) + sprite->GetHeight() / 2
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
			movementDirection = Direction::Up;
			break;
		case TileType::EPD:
			movementDirection = Direction::Down;
			break;
		case TileType::EPL:
			movementDirection = Direction::Left;
			break;
		case TileType::EPR:
			movementDirection = Direction::Right;
			break;
		default:
			throw exception("Invalid tile type");
	}
}

void Enemy::UpdatePosition(float deltaTime)
{
	switch(movementDirection)
	{
		case Direction::Up:
			position.y -= speed * deltaTime;
			break;
		case Direction::Down:
			position.y += speed * deltaTime;
			break;
		case Direction::Left:
			position.x -= speed * deltaTime;
			break;
		case Direction::Right:
			position.x += speed * deltaTime;
			break;
	}
}


void Enemy::UpdateAnimationState()
{
	//if(isIdle) return;

	switch(movementDirection)
	{
		case Direction::Up:
			currentAnimationState = AnimationState::Up;
			break;
		case Direction::Down:
			currentAnimationState = AnimationState::Down;
			break;
		case Direction::Left:
			currentAnimationState = AnimationState::Left;
			break;
		case Direction::Right:
			currentAnimationState = AnimationState::Right;
			break;
	}
}

void Enemy::Animate(float deltaTime)
{
	//if(isIdle)
	//{
	//	sprite->SetFrame(animations[static_cast<int>(currentAnimationState)].startFrame);
	//	animationUpdateTimer = ANIMATION_UPDATE_TIME;
	//	return;
	//}

	if(currentAnimationState != lastAnimationState)
	{
		animationFrame = animations[static_cast<int>(currentAnimationState)].startFrame;
		lastAnimationState = currentAnimationState;
		animationUpdateTimer = ANIMATION_UPDATE_TIME;
	}

	animationUpdateTimer += deltaTime;

	if(animationUpdateTimer > ANIMATION_UPDATE_TIME)
	{
		animationUpdateTimer = 0.0f;

		animationFrame++;
		if(animationFrame > animations[static_cast<int>(currentAnimationState)].endFrame)
		{
			animationFrame = animations[static_cast<int>(currentAnimationState)].startFrame;
		}

		sprite->SetFrame(animationFrame);
	}
}