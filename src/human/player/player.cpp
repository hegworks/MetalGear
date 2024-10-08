#include "precomp.h"
#include "player.h"

#include "src/collider/aabb/boxAabb.h"
#include "src/collider/boxCollider/boxCollider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/tile/tileType.h"

Player::Player(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage) : Human(screen, levelMaps, spriteStorage)
{
	m_pSprite = spriteStorage->GetSpriteData(SpriteType::Player)->sprite;
	m_pSprite->SetFrame(0);

	m_animationFrame = 0;
	m_position = float2(512, 256);
	m_speed = 0.25f;

	tileBoxCollider = new BoxCollider(screen, levelMaps, {30, 30});
	roomChangeCollider = new PointCollider(screen, levelMaps);
	UpdateRoomChangeCollider();

	m_punchBoxAabb = new BoxAabb(GetFeetPos(), {40,40});
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

void Player::CheckPunch()
{
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

void Player::UpdateColliders() const
{
	if(isIdle) return;

	UpdateRoomChangeCollider();
	UpdateTileBoxCollider();
}

void Player::UpdateRoomChangeCollider() const
{
	int2 center =
	{
		static_cast<int>(m_position.x) + tileBoxColliderXOffset + 15,
		static_cast<int>(m_position.y) + tileBoxColliderYOffset + 15
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
}

void Player::UpdateAnimationState()
{
	if(isIdle) return;

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

void Player::Animate(float deltaTime)
{
	if(isIdle)
	{
		m_pSprite->SetFrame(animations[static_cast<int>(m_currentAnimationState)].startFrame);
		animationUpdateTimer = ANIMATION_UPDATE_TIME;
		return;
	}

	if(m_currentAnimationState != m_lastAnimationState)
	{
		m_animationFrame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		m_lastAnimationState = m_currentAnimationState;
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

int2 Player::GetFeetPos() const
{
	const int2 feet =
	{
		static_cast<int>(m_position.x) + m_pSprite->GetWidth() / 2,
		static_cast<int>(m_position.y) + TILESET_TILEHEIGHT * 3
	};
	return feet;
}

void Player::KeyDown(int glfwKey)
{
	switch(glfwKey)
	{
		case GLFW_KEY_F:
			m_isPunchKeyDownAndHaveNotPunched = true;
			break;
	}
}

bool Player::ReportPunch()
{
	if(m_isPunchKeyDownAndHaveNotPunched)
	{
		m_punchBoxAabb->UpdatePosition(m_position);
		m_punchBoxAabb->Draw(m_pScreen, 0xffff00);
		m_isPunchKeyDownAndHaveNotPunched = false;
		return true;
	}
	return false;
}

RoomChangeType Player::ReportRoomChange() const
{
	TileType tileType = roomChangeCollider->GetTileType();
	switch(tileType)
	{
		case TileType::Empty:
		case TileType::Solid:
		case TileType::ESU:
		case TileType::ESD:
		case TileType::ESL:
		case TileType::ESR:
		case TileType::EPU:
		case TileType::EPD:
		case TileType::EPL:
		case TileType::EPR:
		case TileType::Door:
		case TileType::Elevator:
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
			m_position.y = roomChange.newPlayerPos.y;
			break;
		case RoomChangePositionType::LEFT:
		case RoomChangePositionType::RIGHT:
			m_position.x = roomChange.newPlayerPos.x;
			break;
		case RoomChangePositionType::EXCEPTION:
			m_position = roomChange.newPlayerPos;
			break;
		default:
			throw exception("Invalid room change position type");
	}
}

void Player::DrawColliders()
{
	if(isIdle) return;
	tileBoxCollider->Draw(2);
	roomChangeCollider->Draw(5, 0x00FF00FF);
}

float2 Player::GetPosition() const
{
	return m_position;
}

int2 Player::GetFeetTilePosition() const
{
	return m_pLevelMaps->GetTilePos(GetFeetPos());
}
