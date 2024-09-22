#include "precomp.h"
#include "player.h"

#include "src/managers/room/roomChangeType.h"

Player::Player(Surface* screen, LevelMaps* levelMaps) : Human(screen, levelMaps)
{
	spriteAddress = "assets/graphics/playerSheet.png";
	graphicFrames = 42;
	graphic = new Sprite(new Surface(spriteAddress), graphicFrames);
	graphic->SetFrame(0);
	position = float2(512, 256);
	speed = 0.25f;
	animationFrame = 0;

	tileBoxCollider = new BoxCollider(screen, levelMaps, {30, 30});
	roomChangeCollider = new PointCollider(screen, levelMaps);
	UpdateRoomChangeCollider();
}

void Player::Tick(float deltaTime)
{
	HandleInput();
	UpdateColliders();
	UpdatePosition(deltaTime);
	UpdateAnimationState();
	Animate(deltaTime);
}

void Player::HandleInput()
{
	isIdle = false;

	if(GetAsyncKeyState(VK_UP))
	{
		movementDirection = Direction::Up;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		movementDirection = Direction::Down;
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		movementDirection = Direction::Left;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		movementDirection = Direction::Right;
	}
	else
	{
		isIdle = true;
	}
}

void Player::UpdatePosition(float deltaTime)
{
	if(isIdle) return;

	if(tileBoxCollider->IsSolid(movementDirection))
	{
		return;
	}

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

void Player::UpdateColliders() const
{
	if(isIdle) return;

	UpdateRoomChangeCollider();

	int2 feet =
	{
		static_cast<int>(position.x) + tileBoxColliderXOffset,
		static_cast<int>(position.y) + tileBoxColliderYOffset
	};
	switch(movementDirection)
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

	tileBoxCollider->UpdatePosition(feet);
	tileBoxCollider->Draw(2);
}

void Player::UpdateRoomChangeCollider() const
{
	int2 center =
	{
		static_cast<int>(position.x) + tileBoxColliderXOffset + 15,
		static_cast<int>(position.y) + tileBoxColliderYOffset + 15
	};
	switch(movementDirection)
	{
		case Direction::Up:
			center.y -= roomChangeColliderYOffset;
			break;
		case Direction::Down:
			center.y += roomChangeColliderYOffset;
			break;
		case Direction::Left:
			center.x -= roomChangeColliderXOffset;
			break;
		case Direction::Right:
			center.x += roomChangeColliderXOffset;
			break;
	}

	roomChangeCollider->UpdatePosition(center);
	roomChangeCollider->Draw(10, 0x00FF00FF);
}

void Player::UpdateAnimationState()
{
	if(isIdle) return;

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

void Player::Animate(float deltaTime)
{
	if(isIdle)
	{
		graphic->SetFrame(animations[static_cast<int>(currentAnimationState)].startFrame);
		animationUpdateTimer = ANIMATION_UPDATE_TIME;
		return;
	}

	if(currentAnimationState != lastAnimationState)
	{
		animationFrame = animations[static_cast<int>(currentAnimationState)].startFrame;
		lastAnimationState = currentAnimationState;
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

		graphic->SetFrame(animationFrame);
	}
}

RoomChangeType Player::ReportRoomChange() const
{
	TileType tileType = roomChangeCollider->GetTileType();
	switch(tileType)
	{
		case TileType::Empty:
		case TileType::Solid:
			return RoomChangeType::None;
		case TileType::RC0:
			return RoomChangeType::RC0;
		case TileType::RC1:
			return RoomChangeType::RC1;
		case TileType::RC2:
			return RoomChangeType::RC2;
		case TileType::RC3:
			return RoomChangeType::RC3;
		case TileType::RC4:
			return RoomChangeType::RC4;
		default:
			throw exception("Invalid room change type");
	}
}

void Player::RoomChangePos(RoomChange roomChange)
{
	switch(roomChange.positionType)
	{
		case RoomChangePositionType::TOP:
		case RoomChangePositionType::BOTTOM:
			position.y = roomChange.newPlayerPos.y;
			break;
		case RoomChangePositionType::LEFT:
		case RoomChangePositionType::RIGHT:
			position.x = roomChange.newPlayerPos.x;
			break;
		case RoomChangePositionType::EXCEPTION:
			position = roomChange.newPlayerPos;
			break;
		default:
			throw exception("Invalid room change position type");
	}
}
