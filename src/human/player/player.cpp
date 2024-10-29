#include "precomp.h"
#include "player.h"

#include "src/audio/audioManager.h"
#include "src/audio/audioType.h"
#include "src/collider/aabb/boxAabb/boxAabb.h"
#include "src/collider/aabb/circleAabb/circleAabb.h"
#include "src/collider/boxCollider/boxCollider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/managers/hud/hudManager.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"
#include "src/tile/tileType.h"
#include "src/tools/screenPrinter.h"

Player::Player(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, AudioManager* pAudioManager, HudManager* pHudManager) : Human(screen, levelMaps, spriteStorage, pAudioManager)
{
	m_pNormalSprite = spriteStorage->GetSpriteData(SpriteType::Player)->sprite;
	m_pHurtSprite = spriteStorage->GetSpriteData(SpriteType::PlayerHurt)->sprite;
	m_pNormalSprite->SetFrame(0);
	m_pHurtSprite->SetFrame(0);

	m_pSprite = m_pNormalSprite;

	m_pHudManager = pHudManager;

	m_animationFrame = 0;
	m_position = float2(100, 200);
	m_speed = 0.25f;

	m_tileBoxCollider = new BoxCollider(screen, levelMaps, {30, 30});
	m_roomChangeCollider = new PointCollider(screen, levelMaps);
	UpdateRoomChangeCollider();

	m_punchBoxAabb = new BoxAabb(GetFeetPos(), {PUNCH_SIZE,PUNCH_SIZE});
	m_spriteSize = {static_cast<float>(m_pNormalSprite->GetWidth()),static_cast<float>(m_pNormalSprite->GetHeight())};
	m_halfHeightSpriteSize = {m_spriteSize.x, m_spriteSize.y / 2.0f};
	m_enemyBulletBoxAabbTop = new BoxAabb(m_position, m_halfHeightSpriteSize);
	m_enemyBulletBoxAabbBottom = new BoxAabb(GetHalfHeightPosition(), m_halfHeightSpriteSize);

	m_broadPhaseCircleAabb = new CircleAabb(GetCenterPos(), BROAD_PHASE_CIRCLE_AABB_RADIUS);

	m_pHudManager->PlayerHpChanged(m_hp);
}

void Player::Tick(const float deltaTime)
{
	HandleInput();
	UpdateColliders();
	UpdatePosition(deltaTime);
	UpdateAnimationState(deltaTime);
	Animate(deltaTime);
	CheckHurtAnimation(deltaTime);
}

void Player::HandleInput()
{
	m_hasDirectionInput = true;

	if(GetAsyncKeyState(VK_UP))
	{
		m_movementDirection = Direction::Up;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		m_movementDirection = Direction::Down;
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		m_movementDirection = Direction::Left;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		m_movementDirection = Direction::Right;
	}
	else
	{
		m_hasDirectionInput = false;
	}
}

void Player::UpdatePosition(const float deltaTime)
{
	if(!m_hasDirectionInput || m_punchAnimationRemaining > 0) return;

	if(m_tileBoxCollider->IsSolid(m_movementDirection))
	{
		return;
	}

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

void Player::UpdateColliders() const
{
	if(!m_hasDirectionInput) return;

	UpdateRoomChangeCollider();
	UpdateTileBoxCollider();
	UpdateEnemyBulletCollider();
	UpdateBroadPhaseCircleAabb();
}

void Player::UpdateRoomChangeCollider() const
{
	int2 center =
	{
		static_cast<int>(m_position.x) + tileBoxColliderXOffset + 15,
		static_cast<int>(m_position.y) + tileBoxColliderYOffset + 15
	};
	switch(m_movementDirection)
	{
		case Direction::Up:
			center.y -= m_roomChangeColliderYOffset;
			break;
		case Direction::Down:
			center.y += m_roomChangeColliderYOffset;
			break;
		case Direction::Left:
			center.x -= m_roomChangeColliderXOffset;
			break;
		case Direction::Right:
			center.x += m_roomChangeColliderXOffset;
			break;
	}

	m_roomChangeCollider->UpdatePosition(center);
}

void Player::UpdateEnemyBulletCollider() const
{
	m_enemyBulletBoxAabbTop->UpdatePosition(m_position);
	m_enemyBulletBoxAabbBottom->UpdatePosition(GetHalfHeightPosition());
}

void Player::UpdateAnimationState(const float deltaTime)
{
	bool shouldResetToIdleAnimation = false;

	// reduce m_punchAnimationRemaining
	if(m_punchAnimationRemaining > 0)
	{
		m_punchAnimationRemaining -= deltaTime;
		if(m_punchAnimationRemaining < 0)
		{
			m_punchAnimationRemaining = 0;
			shouldResetToIdleAnimation = true;
		}
	}

	// if should start punching in this frame
	if(m_shouldStartPunchAnimation)
	{
		m_shouldStartPunchAnimation = false;
		m_punchAnimationRemaining = PUNCH_ANIMATION_DURATION;

		switch(m_movementDirection)
		{
			case Direction::Up:
				m_currentAnimationState = AnimationType::PunchUp;
				break;
			case Direction::Down:
				m_currentAnimationState = AnimationType::PunchDown;
				break;
			case Direction::Left:
				m_currentAnimationState = AnimationType::PunchLeft;
				break;
			case Direction::Right:
				m_currentAnimationState = AnimationType::PunchRight;
				break;
		}
	}
	else if(m_hasDirectionInput && m_punchAnimationRemaining <= 0 || shouldResetToIdleAnimation)
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
}

void Player::Animate(const float deltaTime)
{
	if(!m_hasDirectionInput && m_punchAnimationRemaining <= 0)
	{
		const int frame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		m_pNormalSprite->SetFrame(frame);
		m_pHurtSprite->SetFrame(frame);
		m_animationUpdateTimer = ANIMATION_UPDATE_TIME;
		return;
	}

	if(m_currentAnimationState != m_lastAnimationState)
	{
		m_animationFrame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		m_lastAnimationState = m_currentAnimationState;
	}

	m_animationUpdateTimer += deltaTime;

	if(m_animationUpdateTimer > ANIMATION_UPDATE_TIME)
	{
		m_animationUpdateTimer = 0.0f;

		m_animationFrame++;
		if(m_animationFrame > animations[static_cast<int>(m_currentAnimationState)].endFrame)
		{
			m_animationFrame = animations[static_cast<int>(m_currentAnimationState)].startFrame;
		}

		m_pNormalSprite->SetFrame(m_animationFrame);
		m_pHurtSprite->SetFrame(m_animationFrame);
	}
}

void Player::UpdateBroadPhaseCircleAabb() const
{
	m_broadPhaseCircleAabb->UpdatePosition(GetCenterPos());
}

void Player::CheckHurtAnimation(float deltaTime)
{
	if(!m_isHurtAnimationPlaying)
	{
		return;
	}

	if(m_hurtAnimationTimer < HURT_ANIMATION_TIME)
	{
		if(m_hurtAnimationIntervalTimer < HURT_ANIMATION_INTERVAL)
		{
			m_hurtAnimationIntervalTimer += deltaTime;
		}
		else
		{
			m_pSprite = m_pSprite == m_pHurtSprite ? m_pNormalSprite : m_pHurtSprite;
			m_hurtAnimationIntervalTimer = 0;
		}

		m_hurtAnimationTimer += deltaTime;
		return;
	}
	m_hurtAnimationTimer = 0;

	m_pSprite = m_pNormalSprite;
	m_isHurtAnimationPlaying = false;
}

float2 Player::GetCenterPos() const
{
	const float width = static_cast<float>(m_pNormalSprite->GetWidth());
	const float height = static_cast<float>(m_pNormalSprite->GetHeight());
	return  {m_position.x + width / 2.0f, m_position.y + height / 2.0f};
}


int2 Player::GetFeetPos() const
{
	const int2 feet =
	{
		static_cast<int>(m_position.x) + m_pNormalSprite->GetWidth() / 2,
		static_cast<int>(m_position.y) + TILESET_TILEHEIGHT * 3
	};
	return feet;
}

void Player::KeyDown(const int glfwKey)
{
	switch(glfwKey)
	{
		case GLFW_KEY_F:
			if(m_punchAnimationRemaining <= 0)
				m_isPunchKeyDownAndHaveNotPunched = true;
			break;
	}
}

void Player::EnemyBulletCollided()
{
	if(m_hp == 0)
	{
		return;
	}

	m_hp--;
	m_isHurtAnimationPlaying = true;
	m_hurtAnimationTimer = 0;
	m_hurtAnimationIntervalTimer = 0;
	m_pAudioManager->Play(AudioType::BulletHit);
	m_pHudManager->PlayerHpChanged(m_hp);
}

void Player::Reset()
{
	m_hp = HP_MAX;
	m_pHudManager->PlayerHpChanged(m_hp);
	m_position = SPAWN_POS;
	m_punchAnimationRemaining = 0;
	m_isHurtAnimationPlaying = false;
	m_currentAnimationState = AnimationType::Down;
	m_lastAnimationState = AnimationType::Down;
	m_animationUpdateTimer = 0;
	m_animationFrame = 0;
	m_pSprite = m_pNormalSprite;
	m_hasDirectionInput = false;
}

bool Player::ReportPunch()
{
	if(m_isPunchKeyDownAndHaveNotPunched)
	{
		// set punch position
		const float2 center = GetCenterPos();
		constexpr float upperBodyYOffset = -20;
		constexpr float punchOffset = 20;
		float2 offset = {0,0};
		switch(m_movementDirection)
		{
			case Direction::Up:
				offset.y -= punchOffset;
				break;
			case Direction::Down:
				offset.y += punchOffset;
				break;
			case Direction::Left:
				offset.x -= punchOffset;
				break;
			case Direction::Right:
				offset.x += punchOffset;
				break;
		}
		float2 punchPos = center + offset - PUNCH_SIZE / 2;
		punchPos.y += upperBodyYOffset;
		m_punchBoxAabb->UpdatePosition(punchPos);

		// debug
		int debug_punchFrameCount = 10;
		m_debug_punchFrameCounter = debug_punchFrameCount;

		m_isPunchKeyDownAndHaveNotPunched = false;
		m_shouldStartPunchAnimation = true;
		return true;
	}
	return false;
}

bool Player::ReportRoomChange()
{
	switch(m_roomChangeCollider->GetTileType())
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
			return false;
		case TileType::RC0:
			m_newRoomChangeType = RoomChangeType::RC0;
			return true;
		case TileType::RC1:
			m_newRoomChangeType = RoomChangeType::RC1;
			return true;
		case TileType::RC2:
			m_newRoomChangeType = RoomChangeType::RC2;
			return true;
		case TileType::RC3:
			m_newRoomChangeType = RoomChangeType::RC3;
			return true;
		case TileType::RC4:
			m_newRoomChangeType = RoomChangeType::RC4;
			return true;
		default:
			throw exception("Invalid room change type");
	}
}

bool Player::ReportWin() const
{
	return m_roomChangeCollider->GetTileType() == TileType::Elevator;
}

bool Player::ReportLose() const
{
	return m_hp <= 0;
}

void Player::RoomChangePos(const RoomChange& roomChange)
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

#ifdef _DEBUG
void Player::DrawColliders()
{
	if(m_debug_punchFrameCounter > 0)
	{
		m_debug_punchFrameCounter--;
		m_punchBoxAabb->Draw(m_pScreen, 0xffff00);
	}

	m_enemyBulletBoxAabbTop->Draw(m_pScreen);
	m_enemyBulletBoxAabbBottom->Draw(m_pScreen);

	m_broadPhaseCircleAabb->Draw(m_pScreen);

	ScreenPrinter* screenPrinter = new ScreenPrinter();
	screenPrinter->Print(m_pScreen, "HP:", m_hp, m_position);
	delete screenPrinter;

	if(!m_hasDirectionInput) return;

	m_tileBoxCollider->Draw(2);
	m_roomChangeCollider->Draw(5, 0x00FF00FF);
}
#endif

float2 Player::GetPosition() const
{
	return m_position;
}

int2 Player::GetFeetTilePosition() const
{
	return m_pLevelMaps->GetTilePos(GetFeetPos());
}
